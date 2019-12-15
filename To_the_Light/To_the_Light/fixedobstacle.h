#pragma once
#include "pch.h"
#include "gameobj.h"

using namespace glm;

class CFixedObstacle : public CGameObject
{
	GLuint m_model_location;
	GLuint m_color_location;
	GLuint m_alpha_location;
	GLuint m_emissive_loction;

	vec3 m_color = vec3(0, 0, 1);

	vec3 m_pos;
	mat4 transform;
	
	GLuint vao;
	GLuint vbo[2];
	std::vector< glm::vec3 > vertex, normal;
	std::vector< glm::vec2 > uv;

	AABB* pAABB;


public:
	CFixedObstacle(vec3 pos);
	~CFixedObstacle();

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	void set_uniform_location(GLuint model_location, GLuint color_location, GLuint, GLuint);

	AABB* get_AABB();
};

