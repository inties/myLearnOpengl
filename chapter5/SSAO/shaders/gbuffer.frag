#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;
layout (location = 3) out vec4 gPosition_view; // 观察空间坐标和深度
layout (location = 4) out vec3 gNormal_view;   // 观察空间法线

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec3 FragPos_view;
in vec3 Normal_view;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{    
    // 存储世界空间的位置
    gPosition = FragPos;
    
    // 存储世界空间的法线
    gNormal = normalize(Normal);
    
    // 存储观察空间的位置和深度
    gPosition_view.rgb = FragPos_view;
    gPosition_view.a = -FragPos_view.z; // 存储线性深度，负值是因为观察空间z轴指向屏幕后方
    
    // 存储观察空间的法线
    gNormal_view = normalize(Normal_view);
    
    // 漫反射颜色
    gAlbedoSpec.rgb = texture(texture_diffuse1, TexCoords).rgb;
    
    // 存储高光强度
    gAlbedoSpec.a = texture(texture_specular1, TexCoords).r;
}
