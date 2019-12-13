#include "camera.h"

CCamera::CCamera(GLuint view_location)
{
	m_view_location = view_location;

	camera_pos = vec3(0, 0, 1);
	camera_center = camera_pos + vec3(0, 0, -1);
	camera_up = vec3(0, 1, 0);

	view = lookAt(camera_pos, camera_center, camera_up);
	glUniformMatrix4fv(m_view_location, 1, GL_FALSE, glm::value_ptr(view));
}

CCamera::~CCamera()
{

}

void CCamera::update()
{
	view = lookAt(camera_pos, camera_center, camera_up);
	glUniformMatrix4fv(m_view_location, 1, GL_FALSE, glm::value_ptr(view));
}

void CCamera::handle_event(GLuint, int, int)
{
}
