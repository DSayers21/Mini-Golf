#version 110

varying vec2 TexCoord0;
uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, TexCoord0);
}