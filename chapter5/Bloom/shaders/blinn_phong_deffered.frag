#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

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

void main()
{             
    // 从 G 缓冲中获取数据
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    // 计算光照
    vec3 lighting = Albedo * 0.1; // 环境光反射
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
    FragColor = vec4(lighting, 1.0);

    // 计算亮度并输出到第二个颜色附件
    float brightness = dot(lighting, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(lighting, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}