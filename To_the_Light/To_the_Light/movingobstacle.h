#pragma once
#include "gameobj.h"

class CMovingObstacle : public CGameObject
{
public:
	CMovingObstacle();
	~CMovingObstacle();

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

};

