#version 330 core
struct Material {
    float     shininess;
}; 


uniform sampler2D diffuse;
uniform sampler2D specular;
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	vec3 direction;

	float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;  
in vec3 Normal;  
  
out vec4 color;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;


in vec2 TexCoords;

void main()
{


    //calculate the distance and then the attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance +light.quadratic * (distance * distance));

   //change the vector the vector light direction, because its pointing from the light towards the objects
   //create a a direction vector pointing towards the light source


   vec3 lightDir = normalize(-light.direction);
    // Ambient
   vec3 ambient = light.ambient * vec3(texture(diffuse, TexCoords));
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse, TexCoords));  
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(specular, TexCoords));

	ambient  *= attenuation;  
    diffuse  *= attenuation;
    specular *= attenuation; 


    color = vec4(ambient + diffuse + specular, 1.0f);
} 






