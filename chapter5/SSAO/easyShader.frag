#version 330 core
layout (location = 0) out vec3 FragColor;




in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;



void main()
{    
    vec3 lightDir=normalize(vec3(1.0,1.0,1.0));
    vec3 ambient=vec3(0.1,0.1,0.1);
    vec3 diffuse=max(dot(Normal,lightDir),0.0)*vec3(0.3,0.3,0.3);
    vec3 specular=pow(max(dot(reflect(-lightDir,Normal),normalize(FragPos)),0.0),32)*vec3(1.0,1.0,1.0);
    FragColor=ambient+diffuse;
    //gamma correction
    FragColor=pow(FragColor,vec3(1.0/2.2));



   

}
