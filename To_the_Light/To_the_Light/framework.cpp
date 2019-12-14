#include "framework.h"
#include "pch.h"
#include "scene.h"
#include "titlescene.h"
#include "gamescene.h"
#include "shader.h"

//#include "endingscene.h"


CFramework::CFramework()
{
}

CFramework::~CFramework()
{
}

void CFramework::Initialize()
{
	init_shader_program(&shader_id, "vertex.glsl", "fragment.glsl");
	glUseProgram(shader_id);
	// GLint model_location = glGetUniformLocation(shader_id, "modelTransform");
	// glm::mat4 model = scale(glm::mat4(1), glm::vec3(1));
	// 
	// glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(model));
	
	cur_time = chrono::system_clock::now();
	enter_scene(Scene::TITLE);
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

	if (cur_scene != nullptr)
		cur_scene->update(frametime);
}

void CFramework::HandleEvent(Event a_event, int mouse_x, int mouse_y)
{
	if (cur_scene != nullptr)
		cur_scene->handle_event(a_event, mouse_x, mouse_y);

}

void CFramework::enter_scene(Scene scene_id)
{
	if (cur_scene) {
		cur_scene->release();
		delete cur_scene;
	}
	cur_scene = nullptr;

	switch (scene_id) {
	case Scene::TITLE :
		cur_scene = new CTitleScene;
		break;
	case Scene::GAME :
		cur_scene = new CGameScene;
		break;
	case Scene::ENDING :
		break;
	}
	cur_scene->initalize(this);
}

GLuint* CFramework::get_shader_id()
{
	return &shader_id;
}
