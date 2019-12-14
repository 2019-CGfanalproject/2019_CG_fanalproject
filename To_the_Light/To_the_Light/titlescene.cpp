#include "titlescene.h"
#include "shader.h"
#include "framework.h"

CTitleScene::CTitleScene()
{
}


CTitleScene::~CTitleScene()
{
}

void CTitleScene::initalize(CFramework* p_fw)
{
	glutWarpPointer(CLIENT_WIDTH / 2, CLIENT_HIEGHT / 2);
	std::cout << "Title" << std::endl;
	m_framework = p_fw;

	shader_id = *m_framework->get_shader_id();
	model_location = glGetUniformLocation(shader_id, "modelTransform");
	veiw_location = glGetUniformLocation(shader_id, "viewTransform");
	projection_location = glGetUniformLocation(shader_id, "projectionTransform");
	object_color_location = glGetUniformLocation(shader_id, "object_color");

	light_pos_location = glGetUniformLocation(shader_id, "lightPos"); //--- lightPos 값 전달
	light_color_location = glGetUniformLocation(shader_id, "lightColor"); //--- lightColor 값 전달
	glUniform3f(light_color_location, 1, 1, 1);
	glUniform3f(light_pos_location, 0, 0, 0.5);


	loadObj("Resource/Object/Title.obj", title_vertex, title_normal, title_uv);

	glGenVertexArrays(1, &title_vao);
	glGenBuffers(2, title_vbo);

	glBindVertexArray(title_vao);

	glBindBuffer(GL_ARRAY_BUFFER, title_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, title_vertex.size() * sizeof(glm::vec3), &title_vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, title_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, title_normal.size() * sizeof(glm::vec3), &title_normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);

	transform = rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)) * scale(mat4(1), vec3(0.5));

	view = lookAt(camera_pos, camera_center, camera_up);
	glUniformMatrix4fv(veiw_location, 1, GL_FALSE, glm::value_ptr(view));
	projection = glm::perspective(glm::radians(90.0f), (float)CLIENT_WIDTH / (float)CLIENT_HIEGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, value_ptr(projection));
}

void CTitleScene::draw()
{
	glBindVertexArray(title_vao);
	glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(transform));
	glUniform3f(object_color_location, 1, 1, 0);
	glDrawArrays(GL_TRIANGLES, 0, title_vertex.size());
}

void CTitleScene::update(std::chrono::milliseconds framtime)
{
}

void CTitleScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{
	if (a_event == Event::RETURN_KEY_DOWN)
		m_framework->enter_scene(Scene::GAME);

	m_mouse_x = mouse_x / (float)CLIENT_WIDTH * 2 - 1;
	m_mouse_y = (CLIENT_HIEGHT - mouse_y) / (float)CLIENT_HIEGHT * 2 - 1;

	glUniform3f(light_pos_location, m_mouse_x, m_mouse_y, -1);
}

void CTitleScene::release()
{
	glClearColor(0, 0, 0.5, 1.0f);
	glutWarpPointer(CLIENT_WIDTH / 2, CLIENT_HIEGHT / 2);
}
