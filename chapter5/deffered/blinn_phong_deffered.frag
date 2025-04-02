#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct Light {
    vec3 Position;
    vec3 Color;
    float Linear;    // 衰减线性项（可选）
    float Quadratic; // 衰减二次项（可选）
};
const int NR_LIGHTS = 1;
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
    vec3 lighting = Albedo * 0.1; // 环境光照分量
    vec3 viewDir = normalize(viewPos - FragPos);

    for(int i = 0; i < NR_LIGHTS; ++i)
    {
        // 漫反射
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * lights[i].Color;

        // 高光（Blinn-Phong 模型）
        vec3 halfwayDir = normalize(lightDir + viewDir); // Blinn-Phong 使用半程向量
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 32.0); // 32.0 是光泽度（Shininess）
        vec3 specular = lights[i].Color * (spec * Specular); // Specular 是从 gAlbedoSpec 中提取的镜面强度

        // 可选：光照衰减（如果你在 C++ 中设置了 Linear 和 Quadratic）
        float distance = length(lights[i].Position - FragPos);
        float attenuation = 1.0 / (1.0 + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);

        // 合并光照贡献
        lighting += (diffuse + specular) ;
    }

    FragColor = vec4(lighting, 1.0);

    // 调试条件（保留你的原始逻辑）
  
}