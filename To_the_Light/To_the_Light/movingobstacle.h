#pragma once
#include "gameobj.h"
#include "pch.h"

#define OBSTACLE_SPEED 2

using namespace glm;

class CMovingObstacle : public CGameObject
{
	int m_state;

	GLuint m_model_location;
	GLuint m_color_location;
	GLuint m_alpha_location;
	GLuint m_emissive_loction;

	vec3 m_color = vec3(0, 0, 1);

	vec3 m_gen_pos;
	vec3 m_pos;
	mat4 transform = mat4(1);
	vec3 dir;

	GLuint vao;
	GLuint vbo[2];
	std::vector< glm::vec3 > vertex, normal;
	std::vector< glm::vec2 > uv;

	AABB* pAABB;

public:
	CMovingObstacle(vec3 pos, int state);
	~CMovingObstacle();

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	void set_uniform_pos(GLuint model_location, GLuint color_location, GLuint alpha_location, GLuint emissive_location);

	void init_buffers();

	AABB* get_AABB();

	void change_dir();

	void update_AABB();
};

bool AABBToAABB(AABB* pAABB1, AABB* pAABB2);