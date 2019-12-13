#pragma once
#include "pch.h"



char* get_filedata_to_buf(const char* filename);
bool init_shader_program(GLuint* id, const char* filename_vert, const char* filename_frag);
int loadObj(const char* filename, std::vector< glm::vec3 >& outvertex,
	std::vector< glm::vec3 >& outnormal, std::vector< glm::vec2 >& outuv);
