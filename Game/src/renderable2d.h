#pragma once

#include "glad/glad.h"
#include "cglm/cglm.h"

#include "buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"

#include <stdlib.h>

typedef struct Renderable2D {
	vec3 position;
	vec2 size;
	vec4 color;

	Vertex_Array *vertex_array;
	Index_Buffer *index_buffer;
	Shader *shader;
}Renderable2D;

void renderable_init(Renderable2D *renderable, vec3 position, vec2 size, vec4 color, Shader *shader);
void renderable_deinit(Renderable2D *renderable);