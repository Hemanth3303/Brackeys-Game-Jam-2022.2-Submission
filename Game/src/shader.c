#include "shader.h"

void shader_init(Shader *shader, const char *vs_filename, const char *fs_filename) {
	char *vs_source, *fs_source;
	GLuint vs_id, fs_id;

	size_t length;
	int succes;
	char infoLog[1024];

	FILE *fptr;
	fptr=fopen(vs_filename, "rt");
	if (!fptr) { 
		printf("couldn't open vs file\n");
		return;
	}
	fseek(fptr, 0L, SEEK_END);
	length=ftell(fptr);
	fseek(fptr, 0L, SEEK_SET);
	vs_source=(char *)calloc(length, sizeof(char));
	if (vs_source) {
		fread(vs_source, sizeof(char), length, fptr);
	}
	fclose(fptr);

	fptr=fopen(fs_filename, "rt");
	if (!fptr) {
		printf("couldn't open fs file\n");
		return;
	}
	fseek(fptr, 0L, SEEK_END);
	length = ftell(fptr);
	fseek(fptr, 0L, SEEK_SET);
	fs_source=(char *)calloc(length, sizeof(char));
	if(fs_source) {
		fread(fs_source, sizeof(char), length, fptr);
	}
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

	shader->id=glCreateProgram();
	glAttachShader(shader->id, vs_id);
	glAttachShader(shader->id, fs_id);
	glLinkProgram(shader->id);

	glGetProgramiv(shader->id, GL_LINK_STATUS, &succes);
	if(!succes) {
		glGetProgramInfoLog(shader->id, 1024, NULL, infoLog);
		printf("Error: Shader Program Linking Error:\n%s\n", infoLog);
	}

	glDeleteShader(vs_id);
	glDeleteShader(fs_id);

	glUseProgram(shader->id);

	free((void *)vs_source);
	free((void *)fs_source);
}

void shader_enable(Shader *shader) {
	glUseProgram(shader->id);
}

void shader_disable(Shader *shader) {
	glUseProgram(0);
}

GLint shader_get_uniform_location(Shader *shader, const GLchar *name) {
	return glGetUniformLocation(shader->id, name);
}

void shader_set_uniform1i(Shader *shader, const GLchar *name, GLint value) {
	glUniform1i(shader_get_uniform_location(shader, name), value);
}

void shader_set_uniform1f(Shader *shader, const GLchar *name, GLfloat value) {
	glUniform1f(shader_get_uniform_location(shader, name), value);
}

void shader_set_uniform2f(Shader *shader, const GLchar *name, GLfloat x, GLfloat y) {
	glUniform2f(shader_get_uniform_location(shader, name), x, y);
}

void shader_set_uniform3f(Shader *shader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z) {
	glUniform3f(shader_get_uniform_location(shader, name), x, y, z);
}

void shader_set_uniform4f(Shader *shader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	glUniform4f(shader_get_uniform_location(shader, name), x, y, z, w);
}

void shader_set_uniform_mat4f(Shader *shader, const GLchar *name, GLfloat *matrix) {
	glUniformMatrix4fv(shader_get_uniform_location(shader, name), 1, GL_FALSE, matrix);
}