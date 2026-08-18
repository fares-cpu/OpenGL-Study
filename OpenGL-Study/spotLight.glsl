#version 330 core

struct Light{
	vec3 position;
	vec3 direction;
	float cos_cutoff;
	float cos_outerCutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main(){
	vec3 diffuseMap = texture(material.diffuse, TexCoord).rgb;
	vec3 specularMap = texture(material.specular, TexCoord).rgb;

	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float dist = length(light.position - FragPos);
	float attenuation = 1 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	float cos_theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cos_cutoff - light.cos_outerCutoff;
	float intensity = clamp(((cos_theta - light.cos_outerCutoff) / epsilon), 0.0, 1.0); 
	vec3 ambient = light.ambient * diffuseMap;

	vec3 diffuse;
	vec3 specular;
	
	float diff = max(dot(norm, lightDir), 0.0);
	diffuse = light.diffuse * diff * diffuseMap;

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	specular = light.specular * spec * specularMap;

	diffuse  *= intensity;
	specular *= intensity;

	FragColor = vec4((ambient + diffuse + specular)*attenuation, 1.0);

	
}