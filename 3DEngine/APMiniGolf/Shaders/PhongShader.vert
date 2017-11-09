#version 120

attribute vec3 Position;
attribute vec2 TexCoord;
attribute vec3 Normal;

varying vec2 TexCoord0;
varying vec3 Normal0;

uniform mat4 Transform; 

void main()
{
	gl_Position = Transform * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
	Normal0 = (Transform * vec4(Normal,1.0)).xyz;
}