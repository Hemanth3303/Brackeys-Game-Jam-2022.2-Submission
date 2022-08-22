#pragma once

#include "glad/glad.h"
#include "cglm/cglm.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Shader {
	GLuint id;	
}Shader;

void shader_init(Shader *shader, const char *vs_filename, const char *fs_filename);
void shader_enable(Shader *shader);
void shader_disable();

GLint shader_get_uniform_location(Shader *shader, const GLchar *name);
void shader_set_uniform1i(Shader *shader, const GLchar *name, GLint value);
void shader_set_uniform1f(Shader *shader, const GLchar *name, GLfloat value);
void shader_set_uniform2f(Shader *shader, const GLchar *name, vec2 vector);
void shader_set_uniform3f(Shader *shader, const GLchar *name, vec3 vector);
void shader_set_uniform4f(Shader *shader, const GLchar *name, vec4 vector);

void shader_set_uniform_mat4f(Shader *shader, const GLchar *name, mat4 matrix);