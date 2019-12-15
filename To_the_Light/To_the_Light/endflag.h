#pragma once
#include "pch.h"
#include "gameobj.h"

using namespace glm;

class CEndFlag: public CGameObject
{
	GLuint vao;
	GLuint vbo[2];
	std::vector< glm::vec3 > vertex, normal;
	std::vector< glm::vec2 > uv;

	GLuint m_model_location;
	GLuint m_color_location;
	GLuint m_alpha_location;
	GLuint m_emissive_location;

	mat4 model = mat4(1);

	vec3 m_pos;
	AABB* pAABB;

public:
	CEndFlag(vec3 pos);
	~CEndFlag();

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	void set_uniform_location
	(GLuint model_location, GLuint color_location, GLuint alpha_location, GLuint emissive_location);

	void init_buffers();

	AABB* get_AABB();
};


