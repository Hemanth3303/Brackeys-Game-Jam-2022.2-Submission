#pragma once

#include "glad/glad.h"

typedef struct Buffer {
	GLuint id;
	GLuint component_count;
}Buffer;

void buffer_init(Buffer *buffer, GLfloat *data, GLsizei count, GLuint component_count);
void buffer_bind(Buffer *buffer);
void buffer_unbind();