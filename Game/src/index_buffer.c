#include "index_buffer.h"

void index_buffer_init(Index_Buffer *index_buffer, GLuint *data, GLsizei count) {
	index_buffer->count=count;

	glGenBuffers(1, &index_buffer->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void index_buffer_bind(Index_Buffer *index_buffer) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
}

void index_buffer_unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}