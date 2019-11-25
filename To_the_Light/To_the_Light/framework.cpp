#include "framework.h"

using namespace std;


CFramework::CFramework()
{
}

CFramework::~CFramework()
{
}

void CFramework::Initialize()
{
	cur_time = chrono::system_clock::now();
}

void CFramework::Release()
{
}

void CFramework::Draw()
{
	if (cur_scene != nullptr)
		cur_scene->draw();
}

void CFramework::Update()
{	
	frametime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - cur_time);
	cur_time = chrono::system_clock::now();
	// cout << frametime.count() << endl;

	if (cur_scene != nullptr)
		cur_scene->update();
}

void CFramework::KeyEvent(Event a_event)
{
}

void CFramework::MouseEvent(Event a_event, int mouse_x, int mouse_y)
{
}

