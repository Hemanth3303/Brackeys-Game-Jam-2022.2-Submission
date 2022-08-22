#pragma once

#include "glad/glad.h"

typedef struct Index_Buffer {
	GLuint id;
	GLuint count;
}Index_Buffer;

void index_buffer_init(Index_Buffer *index_buffer, GLuint *data, GLsizei count);
void index_buffer_bind(Index_Buffer *index_buffer);
void index_buffer_unbind();