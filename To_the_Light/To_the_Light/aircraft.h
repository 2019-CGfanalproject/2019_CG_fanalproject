#pragma once
#include "gameobj.h"
#include <vector>

using namespace glm;


class CAircraft: public CGameObject
{
	GLuint m_model_location;

	float view_x;
	float view_y;

	glm::vec3 pos = { 0,0,0 };
	glm::vec3 direction = glm::vec3{ glm::cos(glm::radians(angle)) , 0 ,  glm::sin(glm::radians(angle)) } *0.2f;
	glm::vec3 height;
	float angle = 270;

	glm::mat4 transform = glm::mat4{ 1.0, };
	glm::mat4 rotate_world = mat4(1);
	glm::mat4 translate_world = mat4(1);
	

	GLuint vao;
	GLuint vbo[2];
	std::vector< glm::vec3 > outvertex, outnormal;
	std::vector< glm::vec2 > outuv;

public:
	CAircraft(GLuint model_location);
	~CAircraft();
	
	virtual void handle_event(Event a_event, int mouse_x, int mouse_y);

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

};

