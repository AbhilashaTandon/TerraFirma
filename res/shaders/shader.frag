#version 330 core

layout(location = 0) out vec4 color;
in vec3 frag_norm;
in vec4 pos;
in vec3 light_dir;
in vec3 frag_color;

void main(){

	float ambient = .5;
	color = vec4(vec3(dot(normalize(light_dir), normalize(frag_norm))) * (1. - ambient) + ambient, 1.);
}