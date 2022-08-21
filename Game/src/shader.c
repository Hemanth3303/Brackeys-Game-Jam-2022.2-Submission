#include "shader.h"

void shader_init(Shader *shader, const char *vs_filename, const char *fs_filename) {
	char *vs_source, *fs_source;
	GLuint vs_id, fs_id;

	long number_of_bytes;

	FILE *fptr;
	fptr=fopen(vs_filename, "r");
	number_of_bytes=ftell(fptr);
	vs_source=(char *)calloc(number_of_bytes, sizeof(char));
	fread(vs_source, sizeof(char), number_of_bytes, fptr);
	fclose(fptr);

	fptr=fopen(fs_filename, "r");
	number_of_bytes=ftell(fptr);
	fs_source=(char *)calloc(number_of_bytes, sizeof(char));
	fread(fs_source, sizeof(char), number_of_bytes, fptr);
	fclose(fptr);
	
	

	free(vs_source);
	free(fs_source);
}

void shader_use(Shader *shader) {

}