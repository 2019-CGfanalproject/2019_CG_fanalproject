#include "gamescene.h"
#include "framework.h"
#include "gameobj.h"
#include "aircraft.h"
#include "camera.h"
#include "map.h"
#include "flag.h"
#include "endflag.h"

CGameScene::CGameScene()
{
}


CGameScene::~CGameScene()
{
}

void CGameScene::initalize(CFramework* p_fw)
{
	std::cout << "���ӽ� ����!" << std::endl;
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
	
	
	create_flags();
	for (list<CFlag*>::iterator it = m_flages.begin(); it != m_flages.end(); it++) {
		(*it)->set_uniform_location(model_location, object_color_location, alpha_location, emissive_location);
	}

	m_end_flag = new CEndFlag(vec3(0, 0, 30));
	m_end_flag->set_uniform_location(model_location, object_color_location, alpha_location, emissive_location);
}

void CGameScene::draw()
{
	glUniform1f(alpha_location, 1.0);
	m_map->draw();
	m_aircraft->draw();
	for (list<CFlag*>::iterator it = m_flages.begin(); it != m_flages.end(); it++) {
		(*it)->draw();
	}
	m_end_flag->draw();
}

void CGameScene::update(std::chrono::milliseconds frametime)
{
	m_aircraft->update(frametime);
	m_camera->update();
	vec3 l_pos = m_aircraft->get_pos();
	glUniform3f(light_pos_location, l_pos.x, l_pos.y + 0.2, l_pos.z);

	for (list<CFlag*>::iterator it = m_flages.begin(); it != m_flages.end(); it++) {
		(*it)->update(frametime);
		if ((*it)->get_AABB()->PointerInBox(m_aircraft->get_pos())) {
			cout << "����" << endl;
			m_aircraft->add_light();
		}
	}

	if (m_end_flag->get_AABB()->PointerInBox(m_aircraft->get_pos())) {
		cout << "������ �Ѿ��" << endl;
		m_framework->enter_scene(Scene::CLEAR);
	}
}

void CGameScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{
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
	glClearColor(0, 0.5, 0, 1.0f);
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
	// ��ġ�� ����ΰ� �����س��� �����
}
