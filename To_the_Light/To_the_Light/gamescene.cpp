#include "gamescene.h"
#include "framework.h"
#include "gameobj.h"
#include "aircraft.h"
#include "camera.h"
#include "map.h"


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
	object_color_location = glGetUniformLocation(shader_id, "object_color");


	projection = glm::perspective(glm::radians(90.0f), (float)CLIENT_WIDTH / (float)CLIENT_HIEGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, value_ptr(projection));

	
	m_map = new CMap();
	m_aircraft = new CAircraft();
	m_camera = new CCamera(veiw_location, m_aircraft);

	m_aircraft->set_uniform_location(model_location, object_color_location);
	m_map->set_uniform_location(model_location, object_color_location);
}

void CGameScene::draw()
{
	m_map->draw();
	m_aircraft->draw();
}

void CGameScene::update(std::chrono::milliseconds frametime)
{
	m_aircraft->update(frametime);
	m_camera->update();
}

void CGameScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{

	m_aircraft->handle_event(a_event,  mouse_x, mouse_y);

}

void CGameScene::release()
{
}
