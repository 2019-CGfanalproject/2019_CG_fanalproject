#pragma once
#include "pch.h"

using namespace std;
using namespace chrono;

class CScene;
class CFramework
{
private:
	system_clock::time_point cur_time;
	milliseconds frametime;

	CScene* cur_scene = { nullptr };
	GLuint shader_id;

public:
	CFramework();
	~CFramework();


	void Initialize();

	void Release();

	void Draw();

	void Update();

	void HandleEvent(Event, int mouse_x, int mouse_y);

	void enter_scene(Scene);
};


