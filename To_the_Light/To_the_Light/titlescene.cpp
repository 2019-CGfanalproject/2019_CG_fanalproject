#include "titlescene.h"
#include "pch.h"
#include "framework.h"

CTitleScene::CTitleScene()
{
}


CTitleScene::~CTitleScene()
{
}

void CTitleScene::initalize(CFramework* p_fw)
{
	std::cout << "Title" << std::endl;
	m_framework = p_fw;
}

void CTitleScene::draw()
{
}

void CTitleScene::update(std::chrono::milliseconds framtime)
{
}

void CTitleScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{
	if (a_event == Event::RETURN_KEY_DOWN)
		m_framework->enter_scene(Scene::GAME);
}

void CTitleScene::release()
{
}
