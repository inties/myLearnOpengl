#version 330 core
out vec4 FragColor;

struct DirectLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirectLight directLight;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


uniform vec3 cameraPos;
unifrom sampler2D texture_diffuse1;
unifrom sampler2D texture_specular1;

void main(){
    vec3 normal=normalize(Normal);
    vec3 viewDir=normalize(cameraPos-FragPos);
    vec3 lightDir = normalize(-directLight.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),32);
    // combine results
    vec3 ambient = directLight.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = directLight.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = directLight.specular * spec * vec3(texture(texture_specular1, TexCoords));
    return (ambient + diffuse + specular);
}