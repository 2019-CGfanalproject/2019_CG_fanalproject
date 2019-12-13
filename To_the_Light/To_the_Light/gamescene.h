#pragma once
#include "scene.h"
#include "pch.h"

class CFramework;

class CGameObject;
class CAircraft;
class CCamera;

class CGameScene : public CScene
{
	CFramework* m_framework{ nullptr };

	GLuint shader_id;
	GLuint model_location;
	GLuint veiw_location;
	GLuint projection_location;
	glm::mat4 projection;
	glm::mat4 model = scale(glm::mat4(1), glm::vec3(0.5));

	CCamera* m_camera;



	GLuint map_vao, map_vbo[2];
	std::vector< glm::vec3 > map_vertex, map_normal;
	std::vector< glm::vec2 > map_uv;

	CAircraft* m_aircraft{ nullptr };
	std::list< CGameObject*> m_game_object;

public:
	CGameScene();
	~CGameScene();

	virtual void initalize(CFramework*);

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	virtual void handle_event(Event a_event, int mouse_x, int mouse_y);


	void init_map();
};
