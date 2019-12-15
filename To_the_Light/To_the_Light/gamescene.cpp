#include "gamescene.h"
#include "framework.h"
#include "gameobj.h"
#include "aircraft.h"
#include "camera.h"
#include "map.h"

#include "flag.h"
#include "endflag.h"

#include "fixedobstacle.h"

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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader_id = *m_framework->get_shader_id();
	get_uniform_location();

	glUniform3f(light_color_location, 0.5, 0.5, 0.5);
	projection = glm::perspective(glm::radians(90.0f), (float)CLIENT_WIDTH / (float)CLIENT_HIEGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, value_ptr(projection));
	
	m_map = new CMap();
	m_map->set_uniform_location(model_location, object_color_location, emissive_location);
	
	m_aircraft = new CAircraft();
	m_aircraft->set_uniform_location(model_location, object_color_location, emissive_location);
	
	m_camera = new CCamera(m_aircraft);
	m_camera->set_uniform_location(veiw_location, camera_pos_location);
	
	create_obstacles();
	for (list<CFixedObstacle*>::iterator it = m_obstacles.begin(); it != m_obstacles.end(); it++) {
		(*it)->set_uniform_location(model_location, object_color_location, alpha_location, emissive_location);
	}

	create_flags();
	for (list<CFlag*>::iterator it = m_flages.begin(); it != m_flages.end(); it++) {
		(*it)->set_uniform_location(model_location, object_color_location, alpha_location, emissive_location);
	}

	m_end_flag = new CEndFlag(vec3(0, 0, 194 - 3.5));
	m_end_flag->set_uniform_location(model_location, object_color_location, alpha_location, emissive_location);
}

void CGameScene::draw()
{
	glUniform1f(alpha_location, 1.0);
	m_map->draw();
	m_aircraft->draw();

	for (list<CFixedObstacle*>::iterator it = m_obstacles.begin(); it != m_obstacles.end(); it++) {
		(*it)->draw();
	}
	
	for (list<CFlag*>::iterator it = m_flages.begin(); it != m_flages.end(); it++) {
		(*it)->draw();
	}

	m_end_flag->draw();
}

void CGameScene::update(std::chrono::milliseconds frametime)
{
	m_aircraft->update(frametime);
	m_camera->update();
	vec3 l_pos = m_camera->get_pos();

	glUniform3f(light_pos_location, l_pos.x, l_pos.y + 0.2, l_pos.z);

	for (list<CFixedObstacle*>::iterator it = m_obstacles.begin(); it != m_obstacles.end(); it++) {
		if ((*it)->get_AABB()->PointerInBox(m_aircraft->get_pos())) {
			m_framework->enter_scene(Scene::GAMEOVER);
			return;
		}
	}

	for (list<CFlag*>::iterator it = m_flages.begin(); it != m_flages.end(); it++) {
		(*it)->update(frametime);
		if ((*it)->get_AABB()->PointerInBox(m_aircraft->get_pos())) {
			cout << "지남" << endl;
			m_aircraft->add_light();
		}
	}

	if (m_end_flag->get_AABB()->PointerInBox(m_aircraft->get_pos())) {
		m_framework->enter_scene(Scene::CLEAR);
		return;
	}

	AABB** walls_aabb = m_map->get_AABB();
	for (int i = 0; i < 7; i++) {
		if (walls_aabb[i]->PointerInBox(m_aircraft->get_pos())) {
			m_framework->enter_scene(Scene::GAMEOVER);
			return;
		}
	}
}

void CGameScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{
	// if (mouse_x > CLIENT_WIDTH - 10) {
	// 	glutWarpPointer(10, CLIENT_HIEGHT / 2);
	// }
	// if (mouse_x < 10) {
	// 	glutWarpPointer(CLIENT_WIDTH - 10, CLIENT_HIEGHT / 2);
	// }
	m_aircraft->handle_event(a_event,  mouse_x, mouse_y);
}

void CGameScene::release()
{
	delete m_camera;
	delete m_map;
	delete m_aircraft;
	delete m_end_flag;

	for (list<CFlag*>::iterator it = m_flages.begin(); it != m_flages.end(); it++) {
		delete *it;
	}
	glClearColor(0, 0, 0, 1.0f);
}

void CGameScene::get_uniform_location()
{
	model_location = glGetUniformLocation(shader_id, "modelTransform");
	veiw_location = glGetUniformLocation(shader_id, "viewTransform");
	projection_location = glGetUniformLocation(shader_id, "projectionTransform");

	camera_pos_location = glGetUniformLocation(shader_id, "cameraPos");
	object_color_location = glGetUniformLocation(shader_id, "object_color");
	light_pos_location = glGetUniformLocation(shader_id, "lightPos");
	light_color_location = glGetUniformLocation(shader_id, "lightColor");
	alpha_location = glGetUniformLocation(shader_id, "alpha");
	emissive_location = glGetUniformLocation(shader_id, "emissive");
}

void CGameScene::create_flags()
{
	CFlag* flag = new CFlag(vec3(0, 3, 5));
	m_flages.push_back(flag);
	// 위치값 어디서인가 정의해놓고 만들기
}

vec3 stand_cylinder_obstacle_pos[] = {
	vec3(0, 0, 35),
	vec3(2.5, 0, 65),
	vec3(-2, 0, 83),
	vec3(3.5, 0, 42),
	vec3(-3.5, 0, 42),
	vec3(80, 0, 96),
	vec3(80, 0, 91),
	vec3(80, 0, 190.5),
	vec3(70, 0, 190.5),
	vec3(60, 0, 192.5),
	vec3(50, 0, 192.5),
};



void CGameScene::create_obstacles()
{
	for (int i = 0; i < 11; i++) {
		CFixedObstacle* tmp = new CFixedObstacle(stage1_obstacle_pos[i]);
		m_obstacles.push_back(tmp);
	}
}


