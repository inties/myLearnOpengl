#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out vec3 FragPos_view;
out vec3 Normal_view;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    // 计算世界空间的法线
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalMatrix * aNormal;
    
    // 计算观察空间的坐标和法线
    FragPos_view = vec3(view * vec4(FragPos, 1.0));
    
    // 正确计算观察空间中的法线 - 需要使用观察空间的法线矩阵
    mat3 normalMatrixView = transpose(inverse(mat3(view)));
    Normal_view = normalMatrixView * Normal;
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}