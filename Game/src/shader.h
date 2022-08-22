#pragma once

#include "glad/glad.h"
#include "cglm/vec2.h"
#include "cglm/vec3.h"
#include "cglm/vec4.h"

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
void shader_set_uniform2f(Shader *shader, const GLchar *name, GLfloat x, GLfloat y);
void shader_set_uniform3f(Shader *shader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
void shader_set_uniform4f(Shader *shader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void shader_set_uniform_mat4f(Shader *shader, const GLchar *name, GLfloat *matrix);