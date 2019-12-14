#pragma once
#include "pch.h"
#include "gameobj.h"

using namespace glm;

class CFixedObstacle : public CGameObject
{
	GLuint m_model_location;
	GLuint m_color_location;
	vec3 m_color = vec3(1, 0, 0);

	vec3 m_pos;
	mat4 transform;
	
	GLuint vao;
	GLuint vbo[2];
	std::vector< glm::vec3 > vertex, normal;
	std::vector< glm::vec2 > uv;


public:
	CFixedObstacle(vec3 pos);
	~CFixedObstacle();

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	void set_uniform_location(GLuint model_location, GLuint color_location);

};

