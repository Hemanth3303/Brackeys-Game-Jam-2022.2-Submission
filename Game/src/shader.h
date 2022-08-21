#pragma once

#include "glad/glad.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Shader {
	GLuint shader_id;	
}Shader;

void shader_init(Shader *shader, const char *vs_filename, const char *fs_filename);
void shader_use(Shader *shader);
void shader_deinit(Shader *shader);