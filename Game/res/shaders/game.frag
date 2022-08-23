#version 330 core

layout (location=0) out vec4 color;

uniform vec2 light_position;

in DATA {
	vec4 position;
	vec4 color;
	vec2 texCoord;
}fs_in;

uniform sampler2D tex;

const float INTENSITY_SCALE=10;

void main() {
	float intensity=1.0f/length(fs_in.position.xy-light_position)*INTENSITY_SCALE;
	vec4 texColor=texture(tex, fs_in.texCoord);
	
	//color=fs_in.color*intensity;

	if(texColor.a<0.1) {
		discard;
	}

	// color=texColor;
	color=texColor*fs_in.color*intensity;
}