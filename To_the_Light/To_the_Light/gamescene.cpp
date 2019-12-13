#include "gamescene.h"
#include "framework.h"
#include "shader.h"
#include "gameobj.h"
#include "aircraft.h"
#include "camera.h"


CGameScene::CGameScene()
{
}


CGameScene::~CGameScene()
{
}

void CGameScene::initalize(CFramework* p_fw)
{
	std::cout << "게임신 시작!" << std::endl;
	m_framework = p_fw;

	shader_id = *m_framework->get_shader_id();
	model_location = glGetUniformLocation(shader_id, "modelTransform");
	veiw_location = glGetUniformLocation(shader_id, "viewTransform");
	projection_location = glGetUniformLocation(shader_id, "projectionTransform");

	projection = glm::perspective(glm::radians(90.0f), (float)CLIENT_WIDTH / (float)CLIENT_HIEGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, value_ptr(projection));


	init_map();

	m_aircraft = new CAircraft(model_location);
	m_camera = new CCamera(veiw_location);

}

void CGameScene::draw()
{
	
	// glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(model));
	// glBindVertexArray(map_vao);
	// glDrawArrays(GL_TRIANGLES, 0, map_vertex.size());

	
	m_aircraft->draw();
}

void CGameScene::update(std::chrono::milliseconds framtime)
{
	m_aircraft->update(frametime);
	m_camera->update();
}

void CGameScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{

	m_aircraft->handle_event(a_event,  mouse_x, mouse_y);

}

void CGameScene::init_map()
{
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

}
