#include "flag.h"
#include "shader.h"

CFlag::CFlag(vec3 pos)
{
	m_pos = pos;
	init_buffers();
	transform = translate(mat4(1), m_pos);
	pAABB = new AABB(
		m_pos.x + 1, m_pos.x - 1, 
		m_pos.y + 1, m_pos.y - 1, 
		m_pos.z + 0.05, m_pos.z - 0.05
	);
}

CFlag::~CFlag()
{
}

void CFlag::draw()
{
	glBindVertexArray(vao);

	glUniformMatrix4fv(m_model_location, 1, GL_FALSE, value_ptr(transform));
	glUniform3f(m_color_location, m_color.x, m_color.y, m_color.z);
	glUniform1f(m_alpha_location, 0.5f);
	glUniform1f(m_emissive_location, 0);
	glDrawArrays(GL_TRIANGLES, 0, vertex.size());
}

void CFlag::update(std::chrono::milliseconds framtime)
{

}

void CFlag::set_uniform_location(GLuint model_location, GLuint color_location, GLuint alpha_location, GLuint emissive_location) {
	m_model_location = model_location;
	m_color_location = color_location;
	m_alpha_location = alpha_location;
	m_emissive_location = emissive_location;
}

void CFlag::init_buffers()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao);

	loadObj("Resource/Object/flag.obj", vertex, normal, uv);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(glm::vec3), &normal[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);

}

vec3 CFlag::get_pos()
{
	return m_pos;
}

AABB* CFlag::get_AABB()
{
	return pAABB;
}
