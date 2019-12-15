#include "clearscene.h"
#include "framework.h"
#include "shader.h"

CClearScene::CClearScene()
{
}

CClearScene::~CClearScene()
{
}

void CClearScene::initalize(CFramework* framework)
{
	m_framework = framework;
	std::cout << "Å¬¸®¾î" << std::endl;

	shader_id = *m_framework->get_shader_id();

	get_uniform_location();
	init_buffers();

	glUniform3f(light_color_location, 1, 1, 1);
	glUniform3f(light_pos_location, 0, 0, 1);
	glUniform1f(alpha_location, 1);

	view = lookAt(camera_pos, camera_center, camera_up);
	glUniformMatrix4fv(veiw_location, 1, GL_FALSE, glm::value_ptr(view));
	projection = glm::perspective(glm::radians(90.0f), (float)CLIENT_WIDTH / (float)CLIENT_HIEGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, value_ptr(projection));

	transform =
		translate(mat4(1), vec3(0, 0, -1)) *
		scale(mat4(1), vec3(0.5));
}

void CClearScene::draw()
{
	glBindVertexArray(clear_vao);
	glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(transform));
	glUniform3f(object_color_location, 0.3, 0.5, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, clear_vertex.size());

}

void CClearScene::update(std::chrono::milliseconds frametime)
{
}

void CClearScene::handle_event(Event a_event, int mouse_x, int mouse_y)
{
	if (a_event == Event::RETURN_KEY_DOWN) {
		m_framework->enter_scene(Scene::TITLE);
	}
}

void CClearScene::release()
{
	glClearColor(0, 0, 0, 1.0f);
}

void CClearScene::get_uniform_location()
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

void CClearScene::init_buffers()
{
	loadObj("Resource/Object/ending.obj", clear_vertex, clear_normal, clear_uv);

	glGenVertexArrays(1, &clear_vao);
	glGenBuffers(2, clear_vbo);

	glBindVertexArray(clear_vao);

	glBindBuffer(GL_ARRAY_BUFFER, clear_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, clear_vertex.size() * sizeof(glm::vec3), &clear_vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, clear_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, clear_normal.size() * sizeof(glm::vec3), &clear_normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);

}
