#version 120

attribute vec3 Position;
attribute vec2 TexCoord;

varying vec2 TexCoord0;

uniform mat4 Transform; 

void main()
{
	gl_Position = Transform * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
}