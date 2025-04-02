#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec3 lightColor;
uniform float emissiveIntensity;

void main()
{
    vec3 color = lightColor * emissiveIntensity;
    FragColor = vec4(color, 1.0);
    
    // 计算亮度并输出到第二个颜色附件
    float brightness = dot(color, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(color, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}