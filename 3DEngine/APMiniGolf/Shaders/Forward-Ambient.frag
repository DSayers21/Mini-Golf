#version 120

varying vec2 TexCoord0;

uniform vec3 R_AmbientIntensity;
uniform sampler2D Diffuse;

void main()
{
	gl_FragColor = texture2D(Diffuse, TexCoord0) * vec4(R_AmbientIntensity,1);
}