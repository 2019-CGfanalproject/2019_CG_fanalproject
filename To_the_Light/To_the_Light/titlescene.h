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

	GLuint light_pos_location;
	GLuint light_color_location;



	mat4 transform = mat4(1);
	mat4 view = mat4(1);
	mat4 projection = mat4(1);

	vec3 camera_pos = vec3(0, 0, 1);
	vec3 camera_center = vec3(0, 0, 0);
	vec3 camera_up = vec3(0, 1, 0);

	GLuint title_vao, title_vbo[2];
	std::vector< glm::vec3 > title_vertex, title_normal;
	std::vector< glm::vec2 > title_uv;

	float m_mouse_x;
	float m_mouse_y;

public:
	CTitleScene();
	~CTitleScene();

	virtual void initalize(CFramework*);

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	virtual void handle_event(Event a_event, int mouse_x, int mouse_y);

	virtual void release();
};