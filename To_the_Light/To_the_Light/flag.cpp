#include "flag.h"


CFlag::CFlag()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao);

	loadObj("Resource/Object/flag.obj", outvertex, outnormal, outuv);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);
}


CFlag::~CFlag()
{
}

void CFlag::draw()
{
	glBindVertexArray(vao);
	glm::mat4 transform =glm::mat4(1);
	glUniformMatrix4fv(m_model_location, 1, GL_FALSE, value_ptr(transform));
	glUniform3f(m_color_location, m_color.x, m_color.y, m_color.z);
	glUniform1f(m_alpha_location, 0.5f);
	glDrawArrays(GL_TRIANGLES, 0, outvertex.size());
}

void CFlag::update(std::chrono::milliseconds framtime)
{

}

void CFlag::set_uniform_location(GLuint model_location, GLuint color_location, GLuint alpha_location) {
	m_model_location = model_location;
	m_color_location = color_location;
	m_alpha_location = alpha_location;
	
}
