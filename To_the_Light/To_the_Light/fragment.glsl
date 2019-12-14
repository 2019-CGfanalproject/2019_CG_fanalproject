#version 330 core

in vec3 FragPos;
in vec3 passColor;
in vec3 Normal;
in vec3 viewPos;
out vec4 FragColor;


uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 ambientLightColor;

void main()
{
	vec3 ambientLight =  vec3(0.2f);
	vec3 ambient = ambientLight*lightColor;

	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseLight = max(dot(Normal,lightDir),0.0);
	vec3 diffuse = diffuseLight * lightColor;
	
	int shininess = 32;
	vec3 viewDir = normalize(FragPos - viewPos);
	vec3 reflectDir = reflect(lightDir, Normal);
	float specularColor = max(dot(viewDir,reflectDir),0.0);
	specularColor = pow(specularColor,shininess);
	vec3 specular = specularColor*lightColor;

	//vec3 emissivelight =vec3(1.0f,1.f,1.f);
	//vec3 emissive = emissivelight*lightColor;


	vec3 result = (ambient + diffuse)*passColor;
	
	FragColor=vec4(result,1.0f);

};