#include "movingobstacle.h"
#include "shader.h"

// state0: diamond
// state1: double pyrimid
// state2: box

CMovingObstacle::CMovingObstacle(vec3 pos, int state)
{
	m_state = state;
	m_pos = pos;
}


CMovingObstacle::~CMovingObstacle()
{
}

void CMovingObstacle::draw()
{
}

void CMovingObstacle::update(std::chrono::milliseconds framtime)
{
}

void CMovingObstacle::init_buffers()
{
	switch (m_state) {
	case 0:
		loadObj("Resource/Object/obstacle_diamond.obj", vertex, normal, uv);
		break;
	case 1:
		loadObj("Resource/Object/obstacle_doublepyramid.obj", vertex, normal, uv);
		break;
	case 2:
		loadObj("Resource/Object/obstacle_box.obj", vertex, normal, uv);
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
