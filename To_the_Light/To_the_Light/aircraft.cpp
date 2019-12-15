#include "aircraft.h"
#include "shader.h"



CAircraft::CAircraft()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao);
	
	loadObj("Resource/Object/aircraft_bear.obj", outvertex, outnormal, outuv);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);

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
	glUniform1f(m_emissive_location, emissive_value);
	
	glDrawArrays(GL_TRIANGLES, 0, outvertex.size());

	// glUniform3f(m_color_location, 1, 0, 0);
	// glLineWidth(5);
	// glBegin(GL_LINE_LOOP);
	// glVertex3d(bounding_box[0].x, bounding_box[0].y, bounding_box[0].z);
	// glVertex3d(bounding_box[1].x, bounding_box[1].y, bounding_box[1].z);
	// glVertex3d(bounding_box[2].x, bounding_box[2].y, bounding_box[2].z);
	// glVertex3d(bounding_box[3].x, bounding_box[3].y, bounding_box[3].z);
	// glEnd();
}

void CAircraft::update(std::chrono::milliseconds a_frametime)
{	
	float frametime = a_frametime.count() / (float)1000;

	if (fly_velocity != 0) {
		fly_rotate = rotate(mat4(1), radians(-10.0f), glm::vec3{ 1,0,0 });
	}
	else {
		fly_rotate = rotate(mat4(1), radians(0.0f), glm::vec3{ 1,0,0 });
	}
	pos.y = pos.y + (fly_velocity - gravity) * frametime;
	pos.y = clamp(pos.y, -1.0f, 9.0f);

	direction = vec3{ sin(radians(angle)) , 0 ,  cos(radians(angle)) };
	right = cross(up, direction);
	pos = pos + direction * vec3(velocity * frametime) + 
			    right * vec3(right_velocity * frametime);		// 방향 이동

	// set_bounding_box();

	translate_world = glm::translate(glm::mat4(1), pos);
	rotate_world = rotate(mat4(1), radians(angle), glm::vec3{ 0,1,0 });

	transform = translate_world * rotate_world * fly_rotate;
}

void CAircraft::handle_event(Event a_event, int mouse_x, int mouse_y) {
	switch (a_event) {
	case W_KEY_DOWN:
		velocity = PLAYER_VELOCITY;
		break;
	case W_KEY_UP:
		velocity = 0;
		break;

	case A_KEY_DOWN:
		right_velocity = PLAYER_VELOCITY;
		break;
	case A_KEY_UP:
		right_velocity = 0;
		break;

	case S_KEY_DOWN:
		velocity = -PLAYER_VELOCITY;

		break;
	case S_KEY_UP:
		velocity = 0;

		break;

	case D_KEY_DOWN:
		right_velocity = -PLAYER_VELOCITY;
		break;
	case D_KEY_UP:
		right_velocity = 0;
		break;

	case SPACE_KEY_DOWN:
		fly_velocity = 5;
		break;
	case SPACE_KEY_UP:
		fly_velocity = 0;
		break;

	case MOUSE_MOTION:
		mouse_x = mouse_x - (CLIENT_WIDTH / 2);
		int delta_x = mouse_x - pre_mouse_x;
		angle -= (delta_x) * 0.2;
		pre_mouse_x = mouse_x;
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

void CAircraft::set_uniform_location(GLuint model_location, GLuint color_location, GLuint emissive_location)
{
	m_model_location = model_location;
	m_color_location = color_location;
	m_emissive_location = emissive_location;
}

vec4* CAircraft::get_vounding_box()
{
	return bounding_box;
}

void CAircraft::add_light()
{
	emissive_value += 0.2;
}


void CAircraft::set_bounding_box()
{
	bounding_box[0] = translate_world * vec4(0, 0.16, 0.7, 0);
	bounding_box[1] = translate_world * vec4(-0.5, 0.16, -0.6, 0);
	bounding_box[2] = translate_world * vec4(0.5, 0.16, -0.6, 0);
	bounding_box[3] = translate_world * vec4(0, 0, -0.6, 0);
}
