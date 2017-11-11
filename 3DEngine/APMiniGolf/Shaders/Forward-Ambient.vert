#version 120

attribute vec3 Position;
attribute vec2 TexCoord;

varying vec2 TexCoord0;

//Model View And Projection
uniform mat4 MVP; 

void main()
{
	gl_Position = MVP * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
}