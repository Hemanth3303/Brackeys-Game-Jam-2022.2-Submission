#include "buffer.h"

void buffer_init(Buffer *buffer, GLfloat *data, GLsizei count, GLuint component_count) {
	buffer->component_count=component_count;
	glGenBuffers(1, &buffer->id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
	glBufferData(GL_ARRAY_BUFFER, count*sizeof(GLfloat), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void buffer_bind(Buffer *buffer) {
	glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
}

void buffer_unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}