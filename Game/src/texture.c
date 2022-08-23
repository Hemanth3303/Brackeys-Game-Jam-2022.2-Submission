#include "texture.h"

void texture_init(Texture *texture, const char *filename) {
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data=stbi_load(filename, &(texture->width), &(texture->height), &(texture->nr_channels), 0);

	glGenTextures(1, &(texture->id));
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);
	stbi_set_flip_vertically_on_load(false);
}

void texture_bind(Texture *texture) {
	glBindTexture(GL_TEXTURE_2D, texture->id);
}

void texture_unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}