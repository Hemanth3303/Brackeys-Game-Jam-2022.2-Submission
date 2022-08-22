#pragma once

#include "glad/glad.h"

#include "buffer.h"

#include <stdlib.h>
#include <stdio.h>

#define MAX_BUFFER_SIZE 1000

typedef struct Vertex_Array {
	GLuint id;
	int current_size;
	Buffer *buffers[MAX_BUFFER_SIZE];
}Vertex_Array;

void vertex_array_init(Vertex_Array *vertex_array);
void vertex_array_deinit(Vertex_Array *vertex_array);
void vertex_array_add_buffer(Vertex_Array *vertex_array, Buffer *buffer, GLuint index);
void vertex_array_bind(Vertex_Array *vertex_array);
void vertex_array_unbind();