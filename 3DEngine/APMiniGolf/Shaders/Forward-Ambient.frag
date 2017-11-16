#version 120

varying vec2 TexCoord0;

uniform vec3 R_AmbientIntensity;
uniform sampler2D R_Diffuse;

void main()
{
	gl_FragColor = texture2D(R_Diffuse, TexCoord0) * vec4(R_AmbientIntensity,1);
}