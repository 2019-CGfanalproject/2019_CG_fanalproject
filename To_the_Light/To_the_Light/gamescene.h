#pragma once
#include "scene.h"


class CFramework;
class CGameObject;
class CAircraft;

class CGameScene : public CScene
{
	CFramework* m_framework{ nullptr };

	GLuint shader_id;



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

};
