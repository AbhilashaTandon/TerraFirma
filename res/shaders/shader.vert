#version 330 core

layout(location = 0) in vec4 pos; //gl_Position is vec4 so this needs to be also
layout(location = 1) in vec3 norm;

out vec3 frag_norm;
out vec4 frag_pos;

uniform float time;

out vec3 camera_pos;
out vec3 light_dir;
out vec3 frag_color;

mat4 look_at(vec3 eye, vec3 center, vec3 up){
	vec3 forward = normalize(center - eye);
	vec3 u = cross(forward, up);
	vec3 v = cross(u, forward);
	vec3 w = -forward;

	mat4 view = mat4(u.x, v.x, w.x, 0,
					 u.y, v.y, w.y, 0,
					 u.z, v.z, w.z, 0,
					 -dot(center, u), -dot(center, v), -dot(center, w), 1);
	
	return view;
}

void main(){

	camera_pos =  vec3(sin(time), -.3, cos(time));

	vec3 camera_target = vec3(0, 0, 0);

	vec3 up = vec3(0, 1, 0);

	mat4 look_at = look_at(camera_pos, camera_target, up);

	light_dir = normalize(vec3(1, 1, 1));

	frag_norm = normalize(norm);

	frag_pos =  look_at * pos;
	frag_color = vec3(1.);

	gl_Position = frag_pos; 
}

