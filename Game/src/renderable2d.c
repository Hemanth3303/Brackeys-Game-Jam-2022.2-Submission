#include "renderable2d.h"

void renderable_init(Renderable2D *renderable, vec3 position, vec2 size, vec4 color, Shader *shader) {
	memcpy(renderable->position, position, 3);
	memcpy(renderable->size, size, 2);
	memcpy(renderable->color, color, 4);

	renderable->vertex_array=(Vertex_Array *)calloc(1, sizeof(Vertex_Array));

	GLfloat vertices[]={
		0, 0, 0,
		0, size[1], 0,
		size[0], size[1], 0,
		size[0], 0, 0
	};

	GLfloat colors[]={
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3]
	};

	Buffer *vertex_buffer=(Buffer *)calloc(1, sizeof(Buffer));
	buffer_init(vertex_buffer, vertices, 4*3, 3);
	Buffer *color_buffer=(Buffer *)calloc(1, sizeof(Buffer));
	buffer_init(color_buffer, colors, 4*4, 4);

	vertex_array_add_buffer(renderable->vertex_array, vertex_buffer, 0);
	vertex_array_add_buffer(renderable->vertex_array, color_buffer, 1);

	GLuint indices[]={
		0, 1, 2,
		2, 3, 0
	};

	renderable->index_buffer=(Index_Buffer *)calloc(1, sizeof(Index_Buffer));
	index_buffer_init(renderable->index_buffer, indices, 6);

}

void renderable_deinit(Renderable2D *renderable) {
	free((void *)renderable->vertex_array);
}