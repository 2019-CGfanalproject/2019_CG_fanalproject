#pragma once
#include "pch.h"

using namespace glm;

class CCamera
{
	GLuint m_view_location;

	float camera_pos_angle;
	float camera_dir_angle;

	vec3 camera_pos;
	vec3 camera_center;
	vec3 camera_up;
	vec3 camera_dir;
	vec3 camera_right;
	mat4 view;

public:
	CCamera(GLuint view_location);
	~CCamera();

	void update();

	void draw();

	void handle_event(GLuint, int, int);
};

