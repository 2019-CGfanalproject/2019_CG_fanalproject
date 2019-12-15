#include "gameoverscene.h"
#include "framework.h"

CGameOverScene::CGameOverScene()
{
}

CGameOverScene::~CGameOverScene()
{
}

void CGameOverScene::initalize(CFramework* framework)
{
	m_framework = framework;
	std::cout << "¿À¹ö" << std::endl;
}

void CGameOverScene::draw()
{
}

void CGameOverScene::update(std::chrono::milliseconds frametime)
{
}

void CGameOverScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{
	if (a_event == Event::RETURN_KEY_DOWN)
		m_framework->enter_scene(TITLE);
}

void CGameOverScene::release()
{
}
