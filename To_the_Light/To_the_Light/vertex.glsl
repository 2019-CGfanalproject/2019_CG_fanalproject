#version 330 core

layout(location=0) in vec3 vPos;
layout(location=1) in vec3 vNormal;

out vec3 FragPos;
out vec3 Normal;
out vec3 viewPos;
out vec3 passColor;

uniform vec3 object_color;
uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	gl_Position =  projectionTransform * viewTransform * modelTransform * vec4(vPos,1.0f);
	//gl_Position = vec4(vPos,1.0f);
	passColor = object_color;

	FragPos = vec3(modelTransform*vec4(vPos,1.0));
	viewPos = vec3(gl_Position);
	Normal = normalize(vNormal);
}