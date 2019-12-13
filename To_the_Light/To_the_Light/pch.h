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
#include <vector>

#pragma comment (lib, "freeglut.lib")
#pragma comment (lib,"glew32.lib")

#define RESOLUTION 160
#define CLIENT_WIDTH	(8 * RESOLUTION)  // 1280
#define CLIENT_HIEGHT	(5 * RESOLUTION)  // 800

typedef enum Event {
	W_KEY_DOWN, W_KEY_UP,
	A_KEY_DOWN, A_KEY_UP,
	S_KEY_DOWN, S_KEY_UP,
	D_KEY_DOWN, D_KEY_UP,
	SPACE_KEY_DOWN, SPACE_KEY_UP,
	RETURN_KEY_DOWN, RETURN_KEY_UP,

}Event;

typedef enum Scene { 
	TITLE, GAME, ENDING
}Scene;
