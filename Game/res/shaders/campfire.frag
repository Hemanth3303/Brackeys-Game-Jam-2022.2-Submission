#version 330 core

layout (location=0) out vec4 color;

uniform vec2 c_light_position;

in DATA {
	vec4 position;
	vec4 color;
	vec2 texCoord;
}fs_in;

uniform sampler2D c_tex;

const float INTENSITY_SCALE=30;

void main() {
	float intensity=1.0f/length(fs_in.position.xy-c_light_position)*INTENSITY_SCALE;
	vec4 texColor=texture(c_tex, fs_in.texCoord);
	
	//color=fs_in.color*intensity;

	if(texColor.a<0.1) {
		discard;
	}

	// color=texColor;
	color=texColor*fs_in.color*intensity;
}