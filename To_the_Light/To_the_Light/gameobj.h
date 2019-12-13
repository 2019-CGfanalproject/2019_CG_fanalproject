#pragma once

class CGameObject
{
public:
	CGameObject();
	~CGameObject();

	virtual void draw() = 0;

	virtual void update() = 0;
};

