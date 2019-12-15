#include "clearscene.h"
#include "framework.h"

CClearScene::CClearScene()
{
}

CClearScene::~CClearScene()
{
}

void CClearScene::initalize(CFramework* framework)
{
	m_framework = framework;
	std::cout << "Å¬¸®¾î" << std::endl;
}

void CClearScene::draw()
{
}

void CClearScene::update(std::chrono::milliseconds frametime)
{
}

void CClearScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{
	if (a_event == Event::RETURN_KEY_DOWN) {
		m_framework->enter_scene(Scene::TITLE);
	}
}

void CClearScene::release()
{
	glClearColor(0, 0, 0, 1.0f);
}
