#version 120

varying vec2 TexCoord0;
varying vec3 Normal0;
varying vec3 WorldPos0;

#include "LightingStructs.glh"

//Uniforms
uniform DirectionalLight R_directionalLight;
uniform sampler2D Diffuse;

#include "Lighting.glh"

void main()
{
	vec4 TotalLight = vec4(0, 0, 0, 1);
	vec4 TextureColour = texture2D(Diffuse, TexCoord0.xy);
	
	vec3 Norm = normalize(Normal0);
	
	TotalLight += CalcDirectionalLight(R_directionalLight, Norm, WorldPos0);
	
	gl_FragColor = TextureColour * TotalLight;
}