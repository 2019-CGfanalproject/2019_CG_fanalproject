#pragma once
#include "scene.h"

class CFramework;
class CTitleScene : public CScene
{
	CFramework* m_framework{ nullptr };

	int m_mouse_x;
	int m_mouse_y;

public:
	CTitleScene();
	~CTitleScene();

	virtual void initalize(CFramework*);

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	virtual void handle_event(Event a_event, int mouse_x, int mouse_y);

	virtual void release();
};