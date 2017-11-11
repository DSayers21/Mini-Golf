#version 120

varying vec2 TexCoord0;

uniform vec3 AmbientIntensity;
uniform sampler2D Sampler;

void main()
{
	gl_FragColor = texture2D(Sampler, TexCoord0) * vec4(AmbientIntensity,1);
}