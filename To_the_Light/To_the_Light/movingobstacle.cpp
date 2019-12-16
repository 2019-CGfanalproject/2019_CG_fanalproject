#include "movingobstacle.h"
#include "shader.h"

// state0: diamond
// state1: double pyrimid
// state2: box

CMovingObstacle::CMovingObstacle(vec3 pos, int state)
{
	m_state = state;
	m_pos = pos;
	m_gen_pos = pos;

	init_buffers();

	transform = translate(mat4(1), m_pos);

}


CMovingObstacle::~CMovingObstacle()
{
}

void CMovingObstacle::draw()
{
	glBindVertexArray(vao);
	glUniformMatrix4fv(m_model_location, 1, GL_FALSE, value_ptr(transform));
	glUniform3f(m_color_location, m_color.x, m_color.y, m_color.z);
	glUniform1f(m_alpha_location, 1);
	glUniform1f(m_emissive_loction, 0);

	glDrawArrays(GL_TRIANGLES, 0, vertex.size());
}

void CMovingObstacle::update(std::chrono::milliseconds a_framtime)
{
	float frametime = a_framtime.count() / (float)1000;

	m_pos += dir * vec3(OBSTACLE_SPEED * frametime);
	transform = translate(mat4(1), m_pos);

	if (m_pos.y > 9) {
		change_dir();
	}

	update_AABB();
}

void CMovingObstacle::set_uniform_pos(GLuint model_location, GLuint color_location, GLuint alpha_location, GLuint emissive_location)
{
	m_model_location = model_location;
	m_color_location = color_location;
	m_alpha_location = alpha_location;
	m_emissive_loction = emissive_location;
}

void CMovingObstacle::init_buffers()
{
	switch (m_state) {
	case 0:
		loadObj("Resource/Object/obstacle_diamond.obj", vertex, normal, uv);
		pAABB = new AABB(
			m_pos.x + 1, m_pos.x - 1,
			m_pos.y + 1, m_pos.y - 1,
			m_pos.z + 1, m_pos.z - 1
			);
		dir = vec3(1, 0, 0);

		break;
	case 1:
		loadObj("Resource/Object/obatacle_doublepyramid.obj", vertex, normal, uv);
		pAABB = new AABB(
			m_pos.x + 1, m_pos.x - 1,
			m_pos.y + 1, m_pos.y - 1,
			m_pos.z + 1, m_pos.z - 1
		);
		dir = vec3(0, 0, 1);

		break;
	case 2:
		loadObj("Resource/Object/box.obj", vertex, normal, uv);
		pAABB = new AABB(
			m_pos.x + 1, m_pos.x - 1,
			m_pos.y + 1, m_pos.y - 1,
			m_pos.z + 1, m_pos.z - 1
		);
		dir = vec3(0, 1, 0);
		break;
	}
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(glm::vec3), &normal[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);
}

AABB* CMovingObstacle::get_AABB()
{
	return pAABB;
}

void CMovingObstacle::change_dir()
{
	dir = -dir;
}

void CMovingObstacle::update_AABB()
{
	pAABB->update_AABB(
		m_pos.x + 1, m_pos.x - 1,
		m_pos.y + 1, m_pos.y - 1,
		m_pos.z + 1, m_pos.z - 1
	);

}
