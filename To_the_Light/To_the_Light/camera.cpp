#include "camera.h"
#include "aircraft.h"

CCamera::CCamera(GLuint view_location, CAircraft* aircraft)
{
	m_view_location = view_location;
	target_obj = aircraft;


	camera_pos = target_obj->get_pos() - (target_obj->get_direction() + distance_to_target);
	camera_center = target_obj->get_pos();
	camera_up = vec3(0, 1, 0);

	view = lookAt(camera_pos, camera_center, camera_up);
	glUniformMatrix4fv(m_view_location, 1, GL_FALSE, glm::value_ptr(view));
}

CCamera::~CCamera()
{

}

void CCamera::update()
{
	camera_pos = target_obj->get_pos() - (target_obj->get_direction() + distance_to_target);
	// camera_pos = target_obj->get_pos() - vec3(0, -0.2, 1) * distance_to_target;
	camera_center = target_obj->get_pos();

	view = lookAt(camera_pos, camera_center, camera_up);
	glUniformMatrix4fv(m_view_location, 1, GL_FALSE, glm::value_ptr(view));
}

void CCamera::handle_event(GLuint, int, int)
{
}
