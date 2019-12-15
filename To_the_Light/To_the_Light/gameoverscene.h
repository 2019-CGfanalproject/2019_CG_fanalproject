#pragma once
#include "pch.h"
#include "scene.h"

class CFramework;
class CGameOverScene: public CScene
{
	CFramework* m_framework{ nullptr };

public:
	CGameOverScene();
	~CGameOverScene();

	virtual void initalize(CFramework*);

	virtual void draw();

	virtual void update(std::chrono::milliseconds frametime);

	virtual void handle_event(Event a_event, int mouse_x, int mouse_y);

	virtual void release();

};

