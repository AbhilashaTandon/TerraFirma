#version 330 core

layout(location = 0) in vec4 pos; //gl_Position is vec4 so this needs to be also

void main(){
	gl_Position = pos; 
}