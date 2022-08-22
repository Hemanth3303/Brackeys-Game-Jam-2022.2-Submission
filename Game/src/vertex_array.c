#include "vertex_array.h"

void vertex_array_init(Vertex_Array *vertex_array) {
	glGenVertexArrays(1, &(vertex_array->id));
	// if(cc_array_new(&vertex_array->buffers)!=CC_OK) {
	// 	printf("Failed to create buffer array in vao\n");
	// 	return;
	// }
}

void vertex_array_deinit(Vertex_Array *vertex_array) {
	// cc_array_destroy(vertex_array->buffers);
}

void vertex_array_add_buffer(Vertex_Array *vertex_array, Buffer *buffer, GLuint index) {
	vertex_array_bind(vertex_array);
	buffer_bind(buffer);

	// if(cc_array_add(vertex_array->buffers, buffer)!=CC_OK) {
	// 	printf("Failed to add buffer to vao\n");
	// }

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->component_count, GL_FLOAT, GL_FALSE, 0, 0);

	buffer_unbind();
	vertex_array_unbind();
}

void vertex_array_bind(Vertex_Array *vertex_array) {
	glBindVertexArray(vertex_array->id);
}

void vertex_array_unbind() {
	glBindVertexArray(0);
}