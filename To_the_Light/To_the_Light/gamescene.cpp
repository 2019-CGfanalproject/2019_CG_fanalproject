#include "gamescene.h"
#include "pch.h"
#include "shader.h"
#include "gameobj.h"
#include "aircraft.h"

CGameScene::CGameScene()
{
}


CGameScene::~CGameScene()
{
}

void CGameScene::initalize(CFramework* p_fw)
{
	std::cout << "게임신 시작!" << std::endl;

	loadObj("Resource/obj/map.obj", map_vertex, map_normal, map_uv);
	
	glGenVertexArrays(1, &map_vao);
	glGenBuffers(2, map_vbo);
	glBindVertexArray(map_vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, map_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, map_vertex.size() * sizeof(glm::vec3), &map_vertex[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);


	m_framework = p_fw;
	m_aircraft = new CAircraft;

}

void CGameScene::draw()
{
	glBindVertexArray(map_vao);
	glDrawArrays(GL_TRIANGLES, 0, map_vertex.size());
	
	m_aircraft->draw();
}

void CGameScene::update(std::chrono::milliseconds framtime)
{
}

void CGameScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{

	m_aircraft->handle_event(a_event,  mouse_x, mouse_y);

}
