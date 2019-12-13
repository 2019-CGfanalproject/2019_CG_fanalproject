#pragma once
#include "pch.h"

class CGameObject
{
public:
	CGameObject();
	~CGameObject();

	virtual void draw() = 0;

	virtual void update(std::chrono::milliseconds framtime) = 0;
};

