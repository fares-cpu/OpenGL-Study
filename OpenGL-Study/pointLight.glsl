#version 330 core

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};


struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};


out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main(){
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	vec3 diffuseMap = texture(material.diffuse, TexCoord).rgb;
	vec3 specularMap = texture(material.specular, TexCoord).rgb;

	float dist = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	
	vec3 ambient = light.ambient * diffuseMap;

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * diffuseMap;

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * specularMap;

	vec3 result  = ambient + diffuse + specular;
	FragColor = vec4(result* attenuation, 1.0);
}