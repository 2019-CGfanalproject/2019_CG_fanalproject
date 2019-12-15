#include "map.h"
#include "shader.h"

CMap::CMap()
{
	init_buffers();
	set_walls_aabb();
}

CMap::~CMap()
{
}

void CMap::update()
{
}

void CMap::draw()
{
	glBindVertexArray(map_vao);

	glUniformMatrix4fv(m_model_location, 1, GL_FALSE, value_ptr(model));
	glUniform3f(m_color_location, 0.3, 0.5, 0.6);
	glUniform1f(m_emissive_location, 0);

	glDrawArrays(GL_TRIANGLES, 0, map_vertex.size());
}

void CMap::set_uniform_location(GLuint model_location, GLuint color_location, GLuint emissive_location)
{
	m_model_location = model_location;
	m_color_location = color_location;
	m_emissive_location = emissive_location;
}

void CMap::init_buffers()
{
	loadObj("Resource/Object/map.obj", map_vertex, map_normal, map_uv);

	glGenVertexArrays(1, &map_vao);
	glGenBuffers(2, map_vbo);
	glBindVertexArray(map_vao);

	glBindBuffer(GL_ARRAY_BUFFER, map_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, map_vertex.size() * sizeof(glm::vec3), &map_vertex[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, map_vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, map_normal.size() * sizeof(glm::vec3), &map_normal[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);
}

AABB** CMap::get_AABB()
{
	return wall_aabbs;
}

void CMap::set_walls_aabb()
{
	wall_aabbs[0] = new AABB(-3.5, -10, 10, 0, 200, 0); // left
	wall_aabbs[2] = new AABB(100, 93.5, 10, 0, 200, 0); // right

	wall_aabbs[1] = new AABB(100, -5, 10, 0, 0, -10); // back
	wall_aabbs[3] = new AABB(100, -5, 10, 0, 200, 194); //front

	wall_aabbs[4] = new AABB(93.5, 3.5, 10, 0, 90, 0); // 1
	wall_aabbs[5] = new AABB(86.5, -5, 10, 0, 187, 97); // 2

	wall_aabbs[6] = new AABB(100, -5, 0, -1, 200, 0); // ¹Ù´Ú
}
