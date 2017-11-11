#version 120

attribute vec3 Position;
attribute vec2 TexCoord;
attribute vec3 Normal;

varying vec2 TexCoord0;
varying vec3 Normal0;
varying vec3 WorldPos0;

uniform mat4 Model; 
uniform mat4 MVP; 

void main()
{
	gl_Position = MVP * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
	Normal0 = normalize(Model * vec4(Normal,0.0)).xyz;
	WorldPos0 = (Model * vec4(Position,1.0)).xyz;
}