#version 330 core
layout (location = 0) out vec3 FragColor;




in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;



void main()
{    

  // Store the fragment position vector in the first gbuffer texture
   //FragColor=texture(texture_diffuse1, TexCoords).rgb;
   FragColor=vec3(1.0,1.0,1.0);
    // Also store the per-fragment normals into the gbuffer


   

}
