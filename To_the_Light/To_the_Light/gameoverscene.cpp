#include "gameoverscene.h"
#include "framework.h"
#include "shader.h"

CGameOverScene::CGameOverScene()
{
}

CGameOverScene::~CGameOverScene()
{
}

void CGameOverScene::initalize(CFramework* framework)
{
	m_framework = framework;
	std::cout << "¿À¹ö" << std::endl;

	shader_id = *m_framework->get_shader_id();

	get_uniform_location();
	init_buffers();

	glUniform3f(light_color_location, 1, 1, 1);
	glUniform3f(light_pos_location, 0, 0, 1);
	glUniform1f(alpha_location, 1);
	glUniform1f(emissive_location, 0);
	glUniform3f(camera_pos_location, camera_pos.x, camera_pos.y, camera_pos.z);

	view = lookAt(camera_pos, camera_center, camera_up);
	glUniformMatrix4fv(veiw_location, 1, GL_FALSE, glm::value_ptr(view));
	projection = glm::perspective(glm::radians(90.0f), (float)CLIENT_WIDTH / (float)CLIENT_HIEGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, value_ptr(projection));

}

void CGameOverScene::draw()
{
	glBindVertexArray(over_vao);
	glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(transform));
	glUniform3f(object_color_location, 0.3, 0.5, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, over_vertex.size());
}

void CGameOverScene::update(std::chrono::milliseconds frametime)
{
}

void CGameOverScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{
	if (a_event == Event::RETURN_KEY_DOWN)
		m_framework->enter_scene(TITLE);
}

void CGameOverScene::release()
{
}

void CGameOverScene::get_uniform_location() 
{
	model_location = glGetUniformLocation(shader_id, "modelTransform");
	veiw_location = glGetUniformLocation(shader_id, "viewTransform");
	projection_location = glGetUniformLocation(shader_id, "projectionTransform");

	camera_pos_location = glGetUniformLocation(shader_id, "cameraPos");
	object_color_location = glGetUniformLocation(shader_id, "object_color");
	light_pos_location = glGetUniformLocation(shader_id, "lightPos");
	light_color_location = glGetUniformLocation(shader_id, "lightColor");
	alpha_location = glGetUniformLocation(shader_id, "alpha");
	emissive_location = glGetUniformLocation(shader_id, "emissive");
}

void CGameOverScene::init_buffers()
{
	loadObj("Resource/Object/gameover.obj", over_vertex, over_normal, over_uv);

	glGenVertexArrays(1, &over_vao);
	glGenBuffers(2, over_vbo);

	glBindVertexArray(over_vao);

	glBindBuffer(GL_ARRAY_BUFFER, over_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, over_vertex.size() * sizeof(glm::vec3), &over_vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, over_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, over_normal.size() * sizeof(glm::vec3), &over_normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);

	transform =
		translate(mat4(1), vec3(0.1, -0.2, -1)) *
		scale(mat4(1), vec3(0.5));

}
