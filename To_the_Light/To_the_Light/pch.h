#pragma once

#include "gl/glew.h"
#include "gl/freeglut.h"
#include "gl/glm/glm.hpp"
#include "gl/glm/ext.hpp"
#include "gl/glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <chrono>
#include <ctime>
#include <list>

#define RESOLUTION 160
#define CLIENT_WIDTH	8 * RESOLUTION
#define CLIENT_HIEGHT	5 * RESOLUTION

typedef enum Event {
}Event;

// 좌표 바꾸는 함수가 필요하다

//int get_world_coord_x(float value) {
//	return (int)((value + 1) * float(CLIENT_WIDTH) / 2.0f);
//}
//
//int get_world_coord_y(float value) {
//	return (int)((-value + 1) * float(CLIENT_HIEGHT) / 2.0f);
//}