#include "aircraft.h"
#include "shader.h"


CAircraft::CAircraft()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao);
	
	loadObj("Resource/Object/aircraft.obj", outvertex, outnormal, outuv);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);



}


CAircraft::~CAircraft()
{
}

void CAircraft::draw()
{
	glBindVertexArray(vao);
	glUniformMatrix4fv(m_model_location, 1, GL_FALSE, value_ptr(transform));
	glUniform3f(m_color_location, m_color.x, m_color.y, m_color.z);
	
	glDrawArrays(GL_TRIANGLES, 0, outvertex.size());
}

void CAircraft::update(std::chrono::milliseconds framtime)
{	
	direction = vec3{ sin(radians(angle)) , 0 ,  cos(radians(angle)) };
	// glm:rotate_world = glm::rotate(rotate_world, glm::radians(-angle), glm::vec3{ 0,1,0 });
	translate_world = glm::translate(glm::mat4(1), pos);

	transform = translate_world;
}


void CAircraft::handle_event(Event a_event, int mouse_x, int mouse_y) {
	switch (a_event) {
	case W_KEY_DOWN:
		pos = pos + direction;
		break;
	case A_KEY_DOWN:
		glm::vec3 left = glm::vec3{ glm::sin(glm::radians(angle + 90)) , 0 ,  glm::cos(glm::radians(angle + 90)) } *0.2f;
		pos = pos + left;
		break;
	case S_KEY_DOWN:
		pos = pos + (-direction);
		break;
	case D_KEY_DOWN:
		glm::vec3 right = glm::vec3{ glm::sin(glm::radians(angle - 90)) , 0 ,  glm::cos(glm::radians(angle - 90)) } *0.2f;
		pos = pos + right;
		break;
	case SPACE_KEY_DOWN:
		glm::vec3 up = glm::vec3{ 0 , glm::sin(glm::radians(angle + 90)) ,  glm::cos(glm::radians(angle + 90)) } *0.2f;
		// pos = pos + up;
		pos = pos + vec3(0, 0.1, 0);

		break;
	}
}

vec3 CAircraft::get_direction()
{
	return direction;
}

vec3 CAircraft::get_pos()
{
	return pos;
}

void CAircraft::set_uniform_location(GLuint model_location, GLuint color_location)
{
	m_model_location = model_location;
	m_color_location = color_location;
}
