#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform sampler2D bloomBuffer;
uniform float exposure;

void main()
{
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
    vec3 bloomColor = texture(bloomBuffer, TexCoords).rgb;
    
    // 合并HDR颜色和Bloom颜色
    //hdrColor += bloomColor;
    
    // 色调映射
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    // gamma校正
    mapped = pow(mapped, vec3(1.0/2.2));
    FragColor = vec4(mapped, 1.0);
}