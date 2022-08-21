#include "shader.h"

void shader_init(Shader *shader, const char *vs_filename, const char *fs_filename) {
	shader=(Shader *)calloc(1, sizeof(Shader));
	char *vs_source, *fs_source;
	GLuint vs_id, fs_id;

	size_t length;
	int succes;
	char infoLog[1024];

	FILE *fptr;
	fptr=fopen(vs_filename, "rt");
	length=ftell(fptr);
	vs_source=(char *)calloc(length, sizeof(char));
	fread(vs_source, sizeof(char), length, fptr);
	fclose(fptr);

	fptr=fopen(fs_filename, "rt");
	length=ftell(fptr);
	fs_source=(char *)calloc(length, sizeof(char));
	fread(fs_source, sizeof(char), length, fptr);
	fclose(fptr);
	
	vs_id=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_id, 1, &vs_source, NULL);
	glCompileShader(vs_id);

	glGetShaderiv(vs_id, GL_COMPILE_STATUS, &succes);
	if(!succes) {
		glGetShaderInfoLog(vs_id, 1024, NULL, infoLog);
		printf("Error: Vertex Shader Compilation Error:\n%s\n", infoLog);
	}
	
	fs_id=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_id, 1, &fs_source, NULL);
	glCompileShader(fs_id);

	glGetShaderiv(fs_id, GL_COMPILE_STATUS, &succes);
	if(!succes) {
		glGetShaderInfoLog(fs_id, 1024, NULL, infoLog);
		printf("Error: Fragment Shader Compilation Error:\n%s\n", infoLog);
	}

	shader->shader_id=glCreateProgram();
	glAttachShader(shader->shader_id, vs_id);
	glAttachShader(shader->shader_id, fs_id);
	glLinkProgram(shader->shader_id);

	glGetProgramiv(shader->shader_id, GL_LINK_STATUS, &succes);
	if(!succes) {
		glGetProgramInfoLog(shader->shader_id, 1024, NULL, infoLog);
		printf("Error: Shader Program Linking Error:\n%s\n", infoLog);
	}

	glDeleteShader(vs_id);
	glDeleteShader(fs_id);

	free((void *)vs_source);
	free((void *)fs_source);
}

void shader_use(Shader *shader) {
	glUseProgram(shader->shader_id);
}

void shader_deinit(Shader *shader) {
	free((void *)shader);
}