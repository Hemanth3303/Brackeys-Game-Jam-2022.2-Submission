#version 330 core

layout (location=0) out vec4 color;

uniform vec2 light_position;

in DATA {
	vec4 position;
	vec4 color;
	vec2 texCoord;
}fs_in;

uniform sampler2D tex;
uniform int lighting_type=0;

const float INTENSITY_SCALE=30;

void main() {
	float intensity=1.0f/length(fs_in.position.xy-light_position)*INTENSITY_SCALE;
	vec4 texColor=texture(tex, fs_in.texCoord);
	
	color=fs_in.color;

	if(texColor.a<0.1) {
		discard;
	}

	// color=texColor;

	if(lighting_type==0) {
		color=texColor*fs_in.color*intensity;
	}
	else if(lighting_type==1) {
		color=texColor*fs_in.color*intensity*vec4(1, 0, 0.5, 1);
	}
	else {
		color=texColor;
	}

}