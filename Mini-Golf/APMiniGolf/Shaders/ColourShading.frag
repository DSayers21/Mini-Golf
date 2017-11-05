#version 120

varying vec2 TexCoord0;
varying vec3 Normal0;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, TexCoord0) * clamp(dot(-vec3(0,0,1), Normal0), 0.0, 1.0);
}