#pragma once
#include "pch.h"
#include "gameobj.h"

#define PLAYER_VELOCITY 3

using namespace glm;


class CAircraft: public CGameObject
{
	GLuint vao;
	GLuint vbo[2];
	std::vector< glm::vec3 > outvertex, outnormal;
	std::vector< glm::vec2 > outuv;

	GLuint m_model_location;
	GLuint m_color_location;
	GLuint m_emissive_location;

	vec3 m_color = vec3(0, 1, 1);
	float emissive_value = 0;

	float gravity = 2;
	float velocity = 0;
	float right_velocity = 0;
	float fly_velocity = 0;

	vec3 pos = { 0, 6, 2 };
	vec3 direction;
	vec3 up = { 0, 1, 0 };
	vec3 right;
	float angle = 0;

	mat4 rotate_world = mat4(1);
	mat4 fly_rotate = mat4(1);
	mat4 translate_world = mat4(1);
	mat4 transform = glm::mat4(1);
	
	int pre_mouse_x = 0;

	vec4 bounding_box[4];


	void set_bounding_box();
public:
	CAircraft();
	~CAircraft();
	
	virtual void handle_event(Event a_event, int mouse_x, int mouse_y);

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	vec3 get_direction();

	vec3 get_pos();

	void set_uniform_location(GLuint model_location, GLuint color_location, GLuint emissive_location);

	vec4* get_vounding_box();

	bool path_flag(vec3 flag_pos);

	void add_light();
};
