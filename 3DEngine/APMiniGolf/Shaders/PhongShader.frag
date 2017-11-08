#version 120

varying vec2 TexCoord0;

uniform vec3 BaseColour;
uniform vec3 AmbientLight;
uniform sampler2D Sampler;

void main()
{
	vec4 TotalLight = vec4(AmbientLight, 1);
	vec4 Colour = vec4(BaseColour, 1);
	vec4 TextureColour = texture2D(Sampler, TexCoord0);
	
	if(Colour == vec4(0,0,0,1))
		Colour = TextureColour;
	
	if(TextureColour != vec4(0,0,0,0))
		Colour *= TextureColour;
		
	gl_FragColor = Colour * TotalLight;
}