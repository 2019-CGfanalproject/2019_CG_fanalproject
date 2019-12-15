#pragma once
#include "pch.h"
#include "scene.h"

using namespace glm;

class CFramework;
class CGameOverScene: public CScene
{
	CFramework* m_framework{ nullptr };

	GLuint shader_id;

	GLuint model_location;
	GLuint veiw_location;
	GLuint projection_location;
	GLuint object_color_location;

	GLuint camera_pos_location;
	GLuint light_pos_location;
	GLuint light_color_location;
	GLuint alpha_location;
	GLuint emissive_location;

	mat4 transform = mat4(1);
	mat4 view = mat4(1);
	mat4 projection = mat4(1);

	vec3 camera_pos = vec3(0, 0, 0);
	vec3 camera_center = vec3(0, 0, -1);
	vec3 camera_up = vec3(0, 1, 0);

	GLuint over_vao, over_vbo[2];
	std::vector< glm::vec3 > over_vertex, over_normal;
	std::vector< glm::vec2 > over_uv;

public:
	CGameOverScene();
	~CGameOverScene();

	virtual void initalize(CFramework*);

	virtual void draw();

	virtual void update(std::chrono::milliseconds frametime);

	virtual void handle_event(Event a_event, int mouse_x, int mouse_y);

	virtual void release();

	void get_uniform_location();

	void init_buffers();
};

