#pragma once
#include "pch.h"

class AABB
{
	float max_x;
	float min_x;
	
	float max_y;
	float min_y;

	float max_z;
	float min_z;

public:
	AABB(float a_max_x, float a_min_x, float a_max_y, float a_min_y, float a_max_z, float a_min_z);
	~AABB();

	float MaxX() { return max_x; };
	float MinX() { return min_x; };

	float MaxY() { return max_y; };
	float MinY() { return min_y; };

	float MaxZ() { return max_z; };
	float MinZ() { return min_z; };

	bool PointerInBox(glm::vec3 pt);
};

