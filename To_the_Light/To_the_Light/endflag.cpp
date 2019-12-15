#include "endflag.h"
#include "shader.h"

CEndFlag::CEndFlag(vec3 pos)
{
	m_pos = pos;
	model = translate(mat4(1), m_pos) * scale(glm::mat4(1), glm::vec3(10));
	pAABB = new AABB(
		m_pos.x + 5, m_pos.x - 5, 
		m_pos.y + 10, m_pos.y, 
		m_pos.z + 5, m_pos.z - 5
	);
	init_buffers();
}

CEndFlag::~CEndFlag()
{
	delete pAABB;
}

void CEndFlag::draw()
{

	glBindVertexArray(vao);

	glUniformMatrix4fv(m_model_location, 1, GL_FALSE, value_ptr(model));
	glUniform3f(m_color_location, 0, 1, 0);
	glUniform1f(m_emissive_location, 0);
	glUniform1f(m_alpha_location, 0.5);

	glDrawArrays(GL_TRIANGLES, 0, vertex.size());

}

void CEndFlag::update(std::chrono::milliseconds framtime)
{
}

void CEndFlag::set_uniform_location(GLuint model_location, GLuint color_location, GLuint alpha_location, GLuint emissive_location)
{
	m_model_location = model_location;
	m_color_location = color_location;
	m_alpha_location = alpha_location;
	m_emissive_location = emissive_location;
}

void CEndFlag::init_buffers()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao);

	loadObj("Resource/Object/box.obj", vertex, normal, uv);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(glm::vec3), &normal[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);

}

AABB* CEndFlag::get_AABB()
{
	return pAABB;
}
