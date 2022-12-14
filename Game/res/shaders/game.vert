#version 330 core

layout (location=0) in vec4 position;
layout (location=1) in vec4 color;
layout (location=2) in vec2 texCoord;

uniform mat4 projection_matrix;
uniform mat4 view_matrix=mat4(1.0);
uniform mat4 model_matrix=mat4(1.0);

out DATA {
	vec4 position;
	vec4 color;
	vec2 texCoord;
}vs_out;

void main() {
	gl_Position=projection_matrix*view_matrix*model_matrix*position;
	vs_out.position=model_matrix*position;
	vs_out.color=color;
	vs_out.texCoord=texCoord;
}