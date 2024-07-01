#version 330 core

layout(location = 0) out vec4 color;
in vec3 frag_norm;
in vec4 pos;
in vec3 light_dir;
in vec3 frag_color;

void main(){
	color = vec4(vec3(dot(light_dir, frag_norm))+.5, 1.);
}