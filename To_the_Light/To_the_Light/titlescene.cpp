#include "titlescene.h"
#include "shader.h"
#include "framework.h"
#include<mmsystem.h>
#pragma comment (lib,"winmm")
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

	get_uniform_location();

	init_title_object();
	PlaySound(TEXT("sound/bgm.wav"), NULL, SND_ASYNC | SND_LOOP);

	glUniform3f(light_color_location, 1, 1, 1);
	glUniform3f(light_pos_location, 0, 0, 1);
	glUniform1f(alpha_location, 1);

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

	glBindVertexArray(mouse_vao);
	glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(cursor_transform));
	glUniform3f(object_color_location, 1, 1, 1);
	glDrawArrays(GL_TRIANGLES, 0, mouse_vertex.size());
}

void CTitleScene::update(std::chrono::milliseconds framtime)
{
	glUniform3f(light_pos_location, m_mouse_x, m_mouse_y, 0);
	cursor_transform = 
		translate(mat4(1), vec3(m_mouse_x, m_mouse_y, -0.5)) * 
		scale(mat4(1), vec3(0.05));

}

void CTitleScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{
	if (a_event == Event::RETURN_KEY_DOWN)
		m_framework->enter_scene(Scene::GAME);

	m_mouse_x = mouse_x / (float)CLIENT_WIDTH * 2 - 1;
	m_mouse_y = -(mouse_y / (float)CLIENT_HIEGHT * 2 - 1);
}

void CTitleScene::release()
{
	glClearColor(0, 0, 0, 1.0f);
	glutWarpPointer(CLIENT_WIDTH / 2, CLIENT_HIEGHT / 2);
}

void CTitleScene::get_uniform_location()
{
	model_location = glGetUniformLocation(shader_id, "modelTransform");
	veiw_location = glGetUniformLocation(shader_id, "viewTransform");
	projection_location = glGetUniformLocation(shader_id, "projectionTransform");
	object_color_location = glGetUniformLocation(shader_id, "object_color");

	light_pos_location = glGetUniformLocation(shader_id, "lightPos"); //--- lightPos 값 전달
	light_color_location = glGetUniformLocation(shader_id, "lightColor"); //--- lightColor 값 전달
	alpha_location = glGetUniformLocation(shader_id, "alpha");
}

void CTitleScene::init_title_object()
{
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

	transform = 
		translate(mat4(1), vec3(0, 0, -1)) * 
		rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)) * 
		scale(mat4(1), vec3(0.5));


	loadObj("Resource/Object/obstacle_diamond.obj", mouse_vertex, mouse_normal, mouse_uv);

	glGenVertexArrays(1, &mouse_vao);
	glGenBuffers(2, mouse_vbo);

	glBindVertexArray(mouse_vao);

	glBindBuffer(GL_ARRAY_BUFFER, mouse_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, mouse_vertex.size() * sizeof(glm::vec3), &mouse_vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, mouse_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, mouse_normal.size() * sizeof(glm::vec3), &mouse_normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);
}
