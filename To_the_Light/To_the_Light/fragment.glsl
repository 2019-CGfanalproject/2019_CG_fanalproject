#version 330 core

in vec3 FragPos;
in vec3 passColor;
in vec3 Normal;
in vec3 viewPos;
out vec4 FragColor;

void main()
{
	FragColor = vec4(passColor, 1.0f);
};