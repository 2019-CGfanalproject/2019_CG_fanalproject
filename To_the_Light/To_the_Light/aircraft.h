#pragma once
#include "pch.h"
#include "gameobj.h"

#define PLAYER_VELOCITY 10

using namespace glm;


class CAircraft: public CGameObject
{
	GLuint m_model_location;
	GLuint m_color_location;
	vec3 m_color = vec3(0, 1, 1);

	float gravity = 2;
	float velocity = 0;
	float right_velocity = 0;
	float fly_velocity = 0;

	vec3 pos = { 0, 2, 1 };
	vec3 direction;
	vec3 up = { 0, 1, 0 };
	vec3 right;
	float angle = 0;

	mat4 transform = glm::mat4(1);
	mat4 rotate_world = mat4(1);
	mat4 translate_world = mat4(1);
	
	int pre_mouse_x = 0;

	GLuint vao;
	GLuint vbo[2];
	std::vector< glm::vec3 > outvertex, outnormal;
	std::vector< glm::vec2 > outuv;

public:
	CAircraft();
	~CAircraft();
	
	virtual void handle_event(Event a_event, int mouse_x, int mouse_y);

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	vec3 get_direction();

	vec3 get_pos();

	void set_uniform_location(GLuint model_location, GLuint color_location);
};
