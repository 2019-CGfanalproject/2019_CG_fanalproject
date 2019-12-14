#pragma once
#include "pch.h"

using namespace glm;
class CAircraft;

class CCamera
{
	GLuint m_view_location;

	CAircraft* target_obj;
	vec3 distance_to_target = vec3(0, -0.5, 3);

	float camera_pos_angle;
	float camera_dir_angle;

	vec3 camera_pos;
	vec3 camera_center;
	vec3 camera_up;
	vec3 camera_dir;
	vec3 camera_right;
	mat4 view;

public:
	CCamera(GLuint view_location, CAircraft* aircraft);
	~CCamera();

	void update();

	void handle_event(GLuint, int, int);
};

