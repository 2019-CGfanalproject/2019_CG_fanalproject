#pragma once
#include "pch.h"

// 씬 흐름도
//					
// 타이틀 -> 플레이 -> 엔딩 -> 타이틀
class CFramework;
class CScene
{
public:
	CScene();
	~CScene();

	virtual void initalize(CFramework*) = 0;

	virtual void draw() = 0;

	virtual void update(std::chrono::milliseconds frametime) = 0;

	virtual void handle_event(Event a_event, int mouse_x, int mouse_y) = 0;

	virtual void release() = 0;
};
