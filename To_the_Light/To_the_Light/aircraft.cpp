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
}
