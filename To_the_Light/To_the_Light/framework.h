#pragma once
#include "pch.h"
#include "scene.h"
#include "strartscene.h"
#include "titlescene.h"
#include "gamescene.h"
#include "endingscene.h"


using namespace std;
using namespace chrono;


class CFramework
{
private:
	system_clock::time_point cur_time;
	milliseconds frametime;

	CScene* cur_scene = { nullptr };

public:
	CFramework();
	~CFramework();


	void Initialize();

	void Release();

	void Draw();

	void Update();

	void KeyEvent(Event a_event);

	void MouseEvent(Event a_event, int mouse_x, int mouse_y);
};

