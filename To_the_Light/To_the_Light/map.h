#pragma once
#include "pch.h"

using namespace glm;

class CMap
{
	GLuint m_model_location;
	GLuint m_color_location;
	GLuint m_emissive_location;

	mat4 model = mat4(1);

	GLuint map_vao, map_vbo[2];
	std::vector< glm::vec3 > map_vertex, map_normal;
	std::vector< glm::vec2 > map_uv;

public:
	CMap();
	~CMap();

	void update();

	void draw();

	void set_uniform_location
	(GLuint model_location, GLuint color_location, GLuint emissive_location);
};

