#version 330 core

layout(location=0) in vec3 vPos;
layout(location=1) in vec3 vNormal;
layout(location=2) in vec2 vUV;


out vec3 FragPos;
out vec3 Normal;
out vec3 passColor;
out vec2 UV;


uniform vec3 object_color;
uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	gl_Position =  projectionTransform * viewTransform * modelTransform * vec4(vPos,1.0f);
	// gl_Position =  modelTransform * vec4(vPos,1.0f);
	//gl_Position = vec4(vPos,1.0f);
	passColor = object_color;

	FragPos = vec3(modelTransform*vec4(vPos,1.0));
	Normal = normalize(vNormal);
	UV = vUV;
}