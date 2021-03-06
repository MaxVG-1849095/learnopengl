#version 330 core
//Shading met lichtbron die rekening houdt met de positie van de kijker
struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  

uniform Material material;
uniform Light light;
uniform vec3 lightPos; //positie van het licht 
uniform vec3 lightColor; //kleur van het licht
uniform vec3 objectColor; //kleur van het object
uniform vec3 viewPos; //positie van de kijker

void main()
{
    // ambient
    vec3 ambient = material.ambient * lightColor * light.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse) * lightColor * light.diffuse;

    // specular
    float specularStrength = 0.5; //sterkte
    vec3 viewDir = normalize(viewPos - FragPos); //kijkrichting vector
    vec3 reflectDir = reflect(-lightDir, norm);   //reflectie vector
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); //
    vec3 specular = specularStrength * spec * material.specular * lightColor * light.specular;  //berekening speculair component


    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 

