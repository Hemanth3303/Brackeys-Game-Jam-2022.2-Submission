#include "renderable2d.h"

void renderable_init(Renderable2D *renderable, vec3 position, vec2 size, vec4 color, Shader *shader, const char *texture_filename) {
	memcpy(renderable->position, position, 3*sizeof(float));
	memcpy(renderable->size, size, 2*sizeof(float));
	memcpy(renderable->color, color, 4*sizeof(float));
	
	if(shader!=NULL){
		renderable->shader=shader;
	}
	
	shader_enable(renderable->shader);
	glActiveTexture(GL_TEXTURE0);
	texture_init(&renderable->texture, texture_filename);
	texture_bind(&renderable->texture);

	renderable->vertex_array=(Vertex_Array *)calloc(1, sizeof(Vertex_Array));
	vertex_array_init(renderable->vertex_array);

	GLfloat vertices[]={
		0, 0, 0,
		0, renderable->size[1], 0,
		renderable->size[0], renderable->size[1], 0,
		renderable->size[0], 0, 0
	};

	GLfloat colors[]={
		renderable->color[0], renderable->color[1], renderable->color[2], renderable->color[3],
		renderable->color[0], renderable->color[1], renderable->color[2], renderable->color[3],
		renderable->color[0], renderable->color[1], renderable->color[2], renderable->color[3],
		renderable->color[0], renderable->color[1], renderable->color[2], renderable->color[3]
	};

	GLfloat tex_coords[]={
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
	};

	Buffer vertex_buffer;
	Buffer color_buffer;
	Buffer texture_buffer;
	buffer_init(&vertex_buffer, vertices, 4*3, 3);
	buffer_init(&color_buffer, colors, 4*4, 4);
	buffer_init(&texture_buffer, tex_coords, 4*2, 2);

	vertex_array_add_buffer(renderable->vertex_array, &vertex_buffer, 0);
	vertex_array_add_buffer(renderable->vertex_array, &color_buffer, 1);
	vertex_array_add_buffer(renderable->vertex_array, &texture_buffer, 2);

	GLuint indices[]={
		0, 1, 2,
		2, 3, 0
	};

	renderable->index_buffer=(Index_Buffer *)calloc(1, sizeof(Index_Buffer));
	index_buffer_init(renderable->index_buffer, indices, 6);
	shader_disable();

}

void renderable_deinit(Renderable2D *renderable) {
	vertex_array_deinit(renderable->vertex_array);
	
	free((void *)renderable->vertex_array);
	free((void *)renderable->index_buffer);
}