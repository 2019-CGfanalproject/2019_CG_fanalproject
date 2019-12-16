#pragma once
#include "scene.h"
#include "pch.h"

#define SNOW_NUM 200

using namespace glm;

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
	glm::vec3 light_color = glm::vec3(0.2);

	CCamera* m_camera{ nullptr };
	CMap* m_map{ nullptr };

	CAircraft* m_aircraft{ nullptr };
	CEndFlag* m_end_flag{ nullptr };
	std::list< CFlag*> m_flages;

	std::list<CFixedObstacle*> m_obstacles;
	std::list<CMovingObstacle*> m_moving_obstacle;

	GLuint snow_vao, snow_vbo[2];
	std::vector< glm::vec3 > snow_vertex, snow_normal;
	std::vector< glm::vec2 > snow_uv;

	mat4 snow_transform[SNOW_NUM];
	vec3 snow_pos[SNOW_NUM];
	vec3 snow_dir = vec3(1, -1, 0);
	float snow_speed[SNOW_NUM];

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

