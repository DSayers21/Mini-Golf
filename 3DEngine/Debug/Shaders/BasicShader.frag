#version 120

varying vec2 TexCoord0;

uniform vec3 BaseColour;
uniform sampler2D Sampler;

void main()
{
	vec4 Colour = vec4(BaseColour, 1);
	vec4 TextureColour = texture2D(Sampler, TexCoord0.xy);
	
	if(Colour == vec4(0,0,0,1))
		Colour = TextureColour;
	
	if(TextureColour != vec4(0,0,0,0))
		Colour *= TextureColour;


	gl_FragColor = texture2D(Sampler, TexCoord0) * Colour;
}