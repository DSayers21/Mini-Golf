#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

varying vec2 TexCoord0;
varying vec3 Normal0;

uniform mat4 Transform; 

void main()
{
	gl_Position = Transform * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
	Normal0 = normalize(Transform * vec4(Normal,0.0)).xyz;
}