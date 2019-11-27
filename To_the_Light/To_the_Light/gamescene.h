#pragma once
#include "scene.h"

class CFramework;
class CGameScene : public CScene
{
	CFramework* m_framework{ nullptr };

public:
	CGameScene();
	~CGameScene();

	virtual void initalize(CFramework*);

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	virtual void handle_event(Event a_event, int mouse_x, int mouse_y);

};
