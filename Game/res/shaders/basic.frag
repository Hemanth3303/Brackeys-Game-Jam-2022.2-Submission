#version 330 core

layout (location=0) out vec4 color;

uniform vec2 light_position;

in DATA {
	vec4 position;
	vec4 color;
}fs_in;

const int INTENSITY_SCALE=30;

void main() {
	float intensity=1.0f/length(fs_in.position.xy-light_position)*INTENSITY_SCALE;
	color=(fs_in.color)*intensity;
}