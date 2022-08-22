#pragma once

#include "glad/glad.h"
// #include "cc_array.h"

#include "buffer.h"

#include <stdio.h>

typedef struct Vertex_Array {
	GLuint id;
	int current_size;
	// CC_Array *buffers;
}Vertex_Array;

void vertex_array_init(Vertex_Array *vertex_array);
void vertex_array_deinit(Vertex_Array *vertex_array);
void vertex_array_add_buffer(Vertex_Array *vertex_array, Buffer *buffer, GLuint index);
void vertex_array_bind(Vertex_Array *vertex_array);
void vertex_array_unbind();