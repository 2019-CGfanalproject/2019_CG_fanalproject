#include "gamescene.h"
#include "pch.h"


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

}

void CGameScene::draw()
{
}

void CGameScene::update(std::chrono::milliseconds framtime)
{
}

void CGameScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{
}
