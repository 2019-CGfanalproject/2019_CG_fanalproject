#pragma once
#include "gameobj.h"
#include <vector>


class CAircraft: public CGameObject
{
	float view_x;
	float view_y;

	GLuint vao;
	GLuint vbo[2];
	std::vector< glm::vec3 > outvertex, outnormal;
	std::vector< glm::vec2 > outuv;

public:
	CAircraft();
	~CAircraft();

	virtual void draw();

	virtual void update();

};

