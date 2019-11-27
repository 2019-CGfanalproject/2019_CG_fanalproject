#pragma once
#include "gameobj.h"


class CAircraft: public CGameObject
{
	float view_x;
	float view_y;

public:
	CAircraft();
	~CAircraft();
};

