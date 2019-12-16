#include "AABB.h"

AABB::AABB(float a_max_x, float a_min_x, float a_max_y, float a_min_y, float a_max_z, float a_min_z)
{
	max_x = a_max_x;
	min_x = a_min_x;

	max_y = a_max_y;
	min_y = a_min_y;

	max_z = a_max_z;
	min_z = a_min_z;

}

AABB::~AABB()
{
}

bool AABB::PointerInBox(glm::vec3 pt)
{
	if (pt.x > max_x) return false;
	if (pt.x < min_x) return false;
	if (pt.y > max_y) return false;
	if (pt.y < min_y) return false;
	if (pt.z > max_z) return false;
	if (pt.z < min_z) return false;

	return true;
}

void AABB::update_AABB(float a_max_x, float a_min_x, float a_max_y, float a_min_y, float a_max_z, float a_min_z)
{
	max_x = a_max_x;
	min_x = a_min_x;

	max_y = a_max_y;
	min_y = a_min_y;

	max_z = a_max_z;
	min_z = a_min_z;

}
