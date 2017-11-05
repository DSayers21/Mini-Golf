#version 120

varying vec3 Colour;

void main()
{
	gl_FragColor = vec4(Colour, 1.0);
}