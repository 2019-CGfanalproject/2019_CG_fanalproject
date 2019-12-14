#pragma once
#include "gameobj.h"
#include "shader.h"
#include "pch.h"

class CFlag : public CGameObject
{
	GLuint m_model_location;
	GLuint m_color_location;
	GLuint m_alpha_location;
	glm::vec3 m_color = glm::vec3(1.0f, 0.0f,0.0f);
	GLuint vao;
	GLuint vbo[2];
	std::vector< glm::vec3 > outvertex, outnormal;
	std::vector< glm::vec2 > outuv;
public:
	CFlag();
	~CFlag();

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	void set_uniform_location(GLuint model_location, GLuint color_location, GLuint alpha_location);

};

