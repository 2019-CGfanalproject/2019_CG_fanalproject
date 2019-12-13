#include "pch.h"
#include "aircraft.h"
#include "shader.h"


CAircraft::CAircraft()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao);
	
	loadObj("Resource/obj/box.obj", outvertex, outnormal, outuv);

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
	glDrawArrays(GL_TRIANGLES, 0, outvertex.size());
}

void CAircraft::update()
{
	transform = translate_world * rotate_world;

}

void CAircraft::handle_event(Event a_event, int mouse_x, int mouse_y) {
	
	switch (a_event) {
	case W_KEY_DOWN:
		pos = pos + direction;
		break;
	case A_KEY_DOWN:
		glm::vec3 left = glm::vec3{ glm::cos(glm::radians(angle - 90)) , 0 ,  glm::sin(glm::radians(angle - 90)) } *0.2f;
		pos = pos + left;
		break;
	case S_KEY_DOWN:
		pos = pos - direction;
		break;
	case D_KEY_DOWN:
		glm::vec3 right = glm::vec3{ glm::cos(glm::radians(angle + 90)) , 0 ,  glm::sin(glm::radians(angle + 90)) } *0.2f;
		pos = pos + right;
		break;
	case SPACE_KEY_UP:
		glm::vec3 up = glm::vec3{ 0 , glm::cos(glm::radians(angle + 90)) ,  glm::sin(glm::radians(angle + 90)) } *0.2f;
		pos = pos + up;
		break;
	}



}