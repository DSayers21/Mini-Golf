#version 120

attribute vec3 Position;

varying vec3 Colour;

uniform mat4 Transform; 

void main()
{
	Colour = vec3(clamp(Position.xyz,0.0,1.0));
	gl_Position = Transform * vec4(Position, 1.0);
}