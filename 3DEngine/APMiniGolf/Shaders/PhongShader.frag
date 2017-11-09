#version 120

varying vec2 TexCoord0;
varying vec3 Normal0;

struct BaseLight
{
	vec3 Colour;
	float Intensity;
};

struct DirectionalLight
{
	BaseLight Light;
	vec3 Direction;
};

uniform vec3 BaseColour;
uniform vec3 AmbientLight;
uniform DirectionalLight directionalLight;
uniform sampler2D Sampler;


vec4 CalcLight(BaseLight Base, vec3 Direction, vec3 Normal)
{
	float DiffuseFactor = dot(-Direction, Normal);
	vec4 DiffuseColour = vec4(0,0,0,0);
	if(DiffuseFactor > 0)
	{
		DiffuseColour = vec4(Base.Colour, 1.0) * Base.Intensity * DiffuseFactor;
	}
	return DiffuseColour;
}

vec4 CalcDirectionalLight(DirectionalLight DirLight, vec3 Normal)
{
	return CalcLight(DirLight.Light, -DirLight.Direction, Normal);
}

void main()
{
	vec4 TotalLight = vec4(AmbientLight, 1);
	vec4 Colour = vec4(BaseColour, 1);
	vec4 TextureColour = texture2D(Sampler, TexCoord0);
	
	if(Colour == vec4(0,0,0,1))
		Colour = TextureColour;
	
	if(TextureColour != vec4(0,0,0,0))
		Colour *= TextureColour;
	
	vec3 Norm = normalize(Normal0);
	
	TotalLight += CalcDirectionalLight(directionalLight, Norm);
		
	gl_FragColor = Colour * TotalLight;
}