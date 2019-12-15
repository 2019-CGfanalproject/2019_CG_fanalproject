#include "camera.h"
#include "aircraft.h"

CCamera::CCamera(CAircraft* aircraft)
{
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
	if (god_view) {
		camera_pos = vec3(48, 50, 48);
		camera_center = camera_pos + vec3(0, -1, 0);
		camera_up = vec3(0, 0, -1);
	}
	else {
		vec3 to_target_pos = target_obj->get_direction();
		to_target_pos = vec3(-to_target_pos.x * 2, 0.5, -to_target_pos.z * 2);
		camera_pos = target_obj->get_pos() + to_target_pos;
		// camera_pos = target_obj->get_pos() - vec3(0, -0.2, 1) * distance_to_target;
		camera_center = target_obj->get_pos();
	}
	view = lookAt(camera_pos, camera_center, camera_up);
	glUniformMatrix4fv(m_view_location, 1, GL_FALSE, glm::value_ptr(view));
	glUniform3f(m_camerapos_location, camera_pos.x, camera_pos.y, camera_pos.z);
}

void CCamera::handle_event(GLuint, int, int)
{
}

void CCamera::set_uniform_location(GLuint view_location, GLuint camerapos_location)
{
	m_view_location = view_location;
	m_camerapos_location = camerapos_location;
}

vec3 CCamera::get_pos()
{
	return camera_pos;
}
