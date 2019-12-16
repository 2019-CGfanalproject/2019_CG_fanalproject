#pragma once
#include "scene.h"
#include "pch.h"

class CFramework;

class CGameObject;
class CAircraft;
class CCamera;
class CMap;
class CFlag;
class CEndFlag;
class CFixedObstacle;
class CMovingObstacle;


class CGameScene : public CScene
{
	CFramework* m_framework{ nullptr };

	GLuint shader_id;

	GLuint model_location;
	GLuint veiw_location;
	GLuint projection_location;
	GLuint object_color_location;

	GLuint light_pos_location;
	GLuint light_color_location;
	GLuint camera_pos_location;
	GLuint alpha_location;
	GLuint emissive_location;

	glm::mat4 projection;

	CCamera* m_camera{ nullptr };
	CMap* m_map{ nullptr };

	CAircraft* m_aircraft{ nullptr };
	CEndFlag* m_end_flag{ nullptr };
	std::list< CFlag*> m_flages;

	std::list<CFixedObstacle*> m_obstacles;
	std::list<CMovingObstacle*> m_moving_obstacle;

public:
	CGameScene();
	~CGameScene();

	virtual void initalize(CFramework*);

	virtual void draw();

	virtual void update(std::chrono::milliseconds framtime);

	virtual void handle_event(Event a_event, int mouse_x, int mouse_y);

	virtual void release();

	void get_uniform_location();

	void create_flags();

	void create_obstacles();

};

