#include "fixedobstacle.h"
#include "shader.h"


// state 0: stand
CFixedObstacle::CFixedObstacle(vec3 pos, int state)
{
	m_pos = pos;


	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao);

	loadObj("Resource/Object/obstacle_sylinder.obj", vertex, normal, uv);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(glm::vec3), &normal[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);

	if (state == 0) {
		transform = translate(mat4(1), m_pos);
		pAABB = new AABB(
			m_pos.x + 1, m_pos.x - 1,
			m_pos.y + 10, m_pos.y,
			m_pos.z + 1, m_pos.z - 1
		);
	}
	else if(state == 1) {
		transform = translate(mat4(1), m_pos) * rotate(mat4(1), radians(90.0f), vec3(0, 0, 1));
		pAABB = new AABB(
			m_pos.x, m_pos.x - 10,
			m_pos.y + 1, m_pos.y - 1,
			m_pos.z + 1, m_pos.z - 1
		);
	}
	else {
		transform = translate(mat4(1), m_pos) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0));
		pAABB = new AABB(
			m_pos.x + 1, m_pos.x - 1,
			m_pos.y + 1, m_pos.y - 1,
			m_pos.z + 10, m_pos.z
		);

	}
}


CFixedObstacle::~CFixedObstacle()
{
	delete pAABB;
}

void CFixedObstacle::draw()
{
	glBindVertexArray(vao);
	glUniformMatrix4fv(m_model_location, 1, GL_FALSE, value_ptr(transform));
	glUniform3f(m_color_location, m_color.x, m_color.y, m_color.z);
	glUniform1f(m_alpha_location, 1);
	glUniform1f(m_emissive_loction, 0);

	glDrawArrays(GL_TRIANGLES, 0, vertex.size());

}

void CFixedObstacle::update(std::chrono::milliseconds framtime)
{
}

void CFixedObstacle::set_uniform_location
(GLuint model_location, GLuint color_location, GLuint alpha_location, GLuint emissive_location)
{
	m_model_location = model_location;
	m_color_location = color_location;
	m_alpha_location = alpha_location;
	m_emissive_loction = emissive_location;
}

AABB* CFixedObstacle::get_AABB()
{
	return pAABB;
}
