#pragma once
#include "scene.h"
#include "pch.h"

using namespace glm;

class CFramework;
class CTitleScene : public CScene
{
	CFramework* m_framework{ nullptr };

	GLuint shader_id;

	GLuint model_location;
	GLuint veiw_location;
	GLuint projection_location;
	GLuint object_color_location;

	mat4 transform = mat4(1);

	GLuint title_vao, title_vbo[2];
	std::vector< glm::vec3 > title_vertex, title_normal;
	std::vector< glm::vec2 > title_uv;

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