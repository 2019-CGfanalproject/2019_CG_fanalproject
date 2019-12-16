#include "gamescene.h"
#include "framework.h"
#include "gameobj.h"
#include "aircraft.h"
#include "camera.h"
#include "map.h"

#include "flag.h"
#include "endflag.h"

#include "fixedobstacle.h"
#include "movingobstacle.h"

vec3 stand_cylinder_obstacle_pos[] = {
	vec3(0, 0, 35),
	vec3(2.5, 0, 65),
	vec3(-2, 0, 83),
	vec3(3.5, 0, 42),
	vec3(-3.5, 0, 42),
	vec3(80, 0, 96),
	vec3(60,0,93.5),
	vec3(80, 0, 91),
	vec3(80, 0, 190.5),
	vec3(70, 0, 190.5),
	vec3(60, 0, 192.5),
	vec3(50, 0, 192.5),
	vec3(90,0,150),
	vec3(87.5,0,135),
	vec3(92.5,0,145),
};

vec3 laydown_cylinder_obstacle_pos[] = {
	vec3(4,0,15),
	vec3(4,8,15),
	vec3(4,4,25),
	vec3(4,2,30),
	vec3(4,2,42),
	vec3(4,9,42),
	vec3(4,4,47),
	vec3(4,2,52),
	vec3(4,6,56),
	vec3(4,8,70),
	vec3(30,7,89),
	vec3(50,7,89),
	vec3(20,7,186),
	//13개
};

vec3 flags_pos[] = {
	vec3(0, 5, 75),
	vec3(0,5,42),
	vec3(90,5,187),
	vec3(90,5,100)
};

vec3 diamond_pos[]{
	// 92~88
	vec3(90.5,6,120),
	vec3(88,4,124),
	vec3(90,5,125),
	vec3(87.5,7,129),
	vec3(89,2,129),
	vec3(90,8,133),
	vec3(91,2,140),
	vec3(88.5,8,143),
	vec3(88,2,163),
	vec3(89,4,165),
	vec3(87.5,5,170),
	vec3(91,8,165),
	vec3(89.5,5,173)
	//13개

};

vec3 double_pyramid_pos[]{
	vec3(33,3,94),
	vec3(37,3,94.5),
	vec3(43,5,91.5),
	vec3(40,8,94.5),
	vec3(43,7,93.5),
	vec3(47,7,94),
	vec3(56,3,94.5),
	vec3(56,5,91),
	vec3(63,6,92),
	vec3(67,7,94),
	vec3(70,7,91.5),
	vec3(55,2,198),
	vec3(45,4,190),
	vec3(35,5,188)
	//14개
};

vec3 box_pos[]{
	vec3(13,5,192.009),
	vec3(13,5,191),
	vec3(13,5,189),

	//7개
	vec3(13,2,192.009),
	vec3(13,2,191),

	//5개
	vec3(13,6,191),
	vec3(13,6,1880.1),

	//5


};


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
	for (list<CMovingObstacle*>::iterator it = m_moving_obstacle.begin(); it != m_moving_obstacle.end(); it++) {
		(*it)->set_uniform_pos(model_location, object_color_location, alpha_location, emissive_location);
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

	for (list<CMovingObstacle*>::iterator it = m_moving_obstacle.begin(); it != m_moving_obstacle.end(); it++) {
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

	if (m_end_flag->get_AABB()->PointerInBox(m_aircraft->get_pos())) {
		m_framework->enter_scene(Scene::CLEAR);
		return;
	}

	for (list<CMovingObstacle*>::iterator it = m_moving_obstacle.begin(); it != m_moving_obstacle.end(); it++) {
		// 업데이트
		(*it)->update(frametime);

		
		// 충돌체크
		AABB** walls_aabb = m_map->get_AABB();
		for (int i = 0; i < 7; i++) {
			if (AABBToAABB((*it)->get_AABB(), walls_aabb[i])) {
				(*it)->change_dir();
			}
		}

		if ((*it)->get_AABB()->PointerInBox(m_aircraft->get_pos())) {
			m_framework->enter_scene(Scene::GAMEOVER);
			return;
		}
	}

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


	//AABB** walls_aabb = m_map->get_AABB();
	//for (int i = 0; i < 7; i++) {
	//	if (walls_aabb[i]->PointerInBox(m_aircraft->get_pos())) {
	//		m_framework->enter_scene(Scene::GAMEOVER);
	//		return;
	//	}
	//}
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

	for (int i = 0; i < 4; i++) {
		CFlag* flag = new CFlag(flags_pos[i]);
		m_flages.push_back(flag);
	}
	// 위치값 어디서인가 정의해놓고 만들기
}

void CGameScene::create_obstacles()
{
	for (int i = 0; i < 15; i++) {
		CFixedObstacle* tmp = new CFixedObstacle(stand_cylinder_obstacle_pos[i], 0);
		m_obstacles.push_back(tmp);
	}
	for (int i = 0; i < 10; i++) {
		CFixedObstacle* tmp = new CFixedObstacle(laydown_cylinder_obstacle_pos[i], 1);
		m_obstacles.push_back(tmp);
	}
	for (int i = 10; i < 13; i++) {
		CFixedObstacle* tmp = new CFixedObstacle(laydown_cylinder_obstacle_pos[i], 2);
		m_obstacles.push_back(tmp);
	}

	for (int i = 0; i < 13; i++) {
		CMovingObstacle* tmp = new CMovingObstacle(diamond_pos[i], 0);
		m_moving_obstacle.push_back(tmp);
	}
	for (int i = 0; i < 14; i++) {
		CMovingObstacle* tmp = new CMovingObstacle(double_pyramid_pos[i], 1);
		m_moving_obstacle.push_back(tmp);
	}
	for (int i = 0; i < 1; i++) {
		CMovingObstacle* tmp = new CMovingObstacle(double_pyramid_pos[i], 2);
		m_moving_obstacle.push_back(tmp);
	}

}


bool AABBToAABB(AABB* pAABB1, AABB* pAABB2)
{
	//x축에대하여
	if (pAABB1->MaxX() < pAABB2->MinX() || pAABB1->MinX() > pAABB2->MaxX()) {
		return false;
	}

	//y축에대하여
	if (pAABB1->MaxY() < pAABB2->MinY() || pAABB1->MinY() > pAABB2->MaxY()) {
		return false;
	}
	
	//z축에대하여
	if (pAABB1->MaxZ() < pAABB2->MinZ() || pAABB1->MinZ() > pAABB2->MaxZ()) {
		return false;
	}

	return true;
}