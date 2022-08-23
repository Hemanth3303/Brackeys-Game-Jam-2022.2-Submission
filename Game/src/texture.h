#pragma once

#include "glad/glad.h"
#include "stb_image.h"

#include <stdbool.h>

typedef struct Texture {
	GLuint id;
	GLsizei width, height, nr_channels;
}Texture;

void texture_init(Texture *texture, const char *filename);
void texture_bind(Texture *texture);
void texture_unbind();