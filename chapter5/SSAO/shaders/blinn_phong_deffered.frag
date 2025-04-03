#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D gNormal_view;
uniform sampler2D gPosition_view;

struct Light {
    vec3 Position;
    vec3 Color;
    float Linear;    // 线性衰减（可选）
    float Quadratic; // 二次衰减（可选）
    float emissiveIntensity; // 发光强度
};
const int NR_LIGHTS = 4;
uniform Light lights[NR_LIGHTS];
uniform vec3 viewPos;

uniform sampler2D noiseTexture;
uniform float radius;
const int nums_samples = 64;
uniform vec3 samples[nums_samples];
uniform mat4 projection;
uniform int SCR_WIDTH, SCR_HEIGHT;

// 获取屏幕空间噪声
vec3 getNoise() {
    // 使用重复模式的噪声纹理
    vec2 noiseScale = vec2(float(SCR_WIDTH)/4.0, float(SCR_HEIGHT)/4.0);
    return normalize(texture(noiseTexture, TexCoords * noiseScale).rgb * 2.0 - 1.0);
}

// 构建TBN矩阵，将采样点从切线空间转换到观察空间
mat3 getTBN() {
    // 获取观察空间的法线
    vec3 normal = normalize(texture(gNormal_view, TexCoords).rgb);
    
    // 计算切线向量 - 使用噪声纹理避免重复模式
    vec3 randVec = getNoise();
    vec3 tangent = normalize(randVec - normal * dot(randVec, normal));
    vec3 bitangent = cross(normal, tangent);
    
    return mat3(tangent, bitangent, normal);
}

// 线性插值函数
float lerp(float a, float b, float f) {
    return a + (b - a) * f;
}

// 计算SSAO
float SSAO() {
    // 获取当前片段在观察空间的信息
    vec3 fragPos = texture(gPosition_view, TexCoords).xyz;
    float fragDepth = fragPos.z; // 观察空间的z值是负的（越远越负）
    
    // 获取TBN矩阵
    mat3 TBN = getTBN();
    
    // 遮蔽计数器
    float occlusion = 0.0;
    
    // 处理所有采样点
    for(int i = 0; i < nums_samples; i++) {
        // 将采样点从切线空间转换到观察空间
        vec3 samplePos = TBN * samples[i];
        samplePos = fragPos + samplePos * radius;
        
        // 将采样点投影到屏幕空间
        vec4 offset = projection * vec4(samplePos, 1.0);
        offset.xyz /= offset.w;
        offset.xyz = offset.xyz * 0.5 + 0.5; // 将[-1,1]转换为[0,1]
        
        // 获取采样点在观察空间的深度
        float sampleDepth = texture(gPosition_view, offset.xy).z;
        
        // 检查是否有遮挡
        float bias = 0.025; // 避免自遮挡的偏移量
        
        // 范围检查避免边缘伪影
        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragDepth - sampleDepth));
        
        // 正确的遮挡检测逻辑：
        // 在观察空间中，z轴指向屏幕后方，所以z值越小（越负）表示越远
        // 如果采样点的深度小于（更负）当前片段的深度，则采样点在当前片段后面，表示有遮挡
        // 注意：在观察空间中深度越负离相机越远，所以需要判断sampleDepth < samplePos.z
        occlusion += (sampleDepth > samplePos.z - bias ? 1.0 : 0.0) * rangeCheck;
    }
    
    // 归一化并反转结果（0表示完全遮挡，1表示没有遮挡）
    occlusion = 1.0 - (occlusion / float(nums_samples));
    
    // 应用非线性映射以强调遮挡区域
    return pow(occlusion, 2.0);
}

void main()
{             
    // 从 G 缓冲中获取数据
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    // 计算环境光遮蔽
    float aoFactor = SSAO();
    
    // 计算光照
    vec3 lighting = Albedo * 0.1 ; // 应用SSAO到环境光
    vec3 viewDir = normalize(viewPos - FragPos);

    for(int i = 0; i < NR_LIGHTS; ++i)
    {
        // 漫反射
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * lights[i].Color * lights[i].emissiveIntensity;

        // 高光（Blinn-Phong 模型）
        vec3 halfwayDir = normalize(lightDir + viewDir); // Blinn-Phong 使用半程向量
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 32.0); // 32.0 是光泽度（Shininess）
        vec3 specular = lights[i].Color * (spec * Specular) * lights[i].emissiveIntensity; // Specular 是从 gAlbedoSpec 获取的镜面强度

        // 可选的距离衰减，从 C++ 代码中获取 Linear 和 Quadratic
        float distance = length(lights[i].Position - FragPos);
        float attenuation = 1.0 / (1.0 + lights[i].Linear * distance);
        // 合并光照结果
        lighting += (diffuse + specular) * attenuation;
    }

    // 输出到第一个颜色附件
    
    FragColor=vec4(aoFactor,aoFactor,aoFactor,1.0);
    
    // 计算亮度并输出到第二个颜色附件
    float brightness = dot(lighting, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0){
        BrightColor = vec4(lighting, 1.0);
    }
    else{
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    
    // 无论是否超过亮度阈值，都保留正常的光照结果
    //FragColor = vec4(lighting, 1.0);
}