#pragma once
#include "gameobj.h"
#include "pch.h"

using namespace glm;


class CFlag : public CGameObject
{
	GLuint vao;
	GLuint vbo[2];
	std::vector< glm::vec3 > vertex, normal;
	std::vector< glm::vec2 > uv;

	GLuint m_model_location;
	GLuint m_color_location;
	GLuint m_alpha_location;
	GLuint m_emissive_location;

	vec3 m_pos;
	vec3 m_color = glm::vec3(1.0f, 0.0f,0.0f);

	mat4 transform;

	AABB* pAABB;

	bool pass_flag = false;

public:
	CFlag(vec3 pos);
	~CFlag();

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	void set_uniform_location
	(GLuint model_location, GLuint color_location, GLuint alpha_location, GLuint emissive_location);

	void init_buffers();

	vec3 get_pos();

	AABB* get_AABB();

	void check_pass() {
		pass_flag = true;
	}

	bool get_pass() {
		return pass_flag;
	}
};

