#version 330 core

in vec3 FragPos;
in vec3 passColor;
in vec3 Normal;
in vec2 UV;
out vec4 FragColor;


uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 cameraPos;
uniform float alpha;
uniform float emissive;
uniform sampler2D myTexture;

int shininess = 32;

void main()
{
	vec3 ambient_intensity =  vec3(0.2f);
	vec3 ambient_light = ambient_intensity * lightColor;

	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(FragPos - cameraPos);
	vec3 reflectDir = reflect(lightDir, Normal);

	float diffuse_intensity = max(dot(Normal,lightDir),0.0);
	vec3 diffuse_light = diffuse_intensity * lightColor;

	float specular_intensity = max(dot(viewDir, reflectDir),0.0);
	specular_intensity = pow(specular_intensity, shininess);
	vec3 specular_light = specular_intensity * lightColor;

	vec3 emissive_intensity = vec3(emissive);
	vec3 emissive_light = emissive_intensity * lightColor;

//	vec3 result = (ambient_light + diffuse_light + specular_light) * texture(myTexture,UV).rgb + emissive;
	vec3 result = (ambient_light + diffuse_light + specular_light) * passColor + emissive;
	
	FragColor=vec4(result, alpha);
};