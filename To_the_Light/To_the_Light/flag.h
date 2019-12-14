#pragma once
#include "gameobj.h"

class CFlag : public CGameObject
{
public:
	CFlag();
	~CFlag();

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);
};

