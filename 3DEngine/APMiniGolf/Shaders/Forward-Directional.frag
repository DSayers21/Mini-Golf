#version 120

varying vec2 TexCoord0;
varying vec3 Normal0;
varying vec3 WorldPos0;

struct BaseLight {
	vec3 Colour;
	float Intensity;
};

struct DirectionalLight {
	BaseLight Light;
	vec3 Direction;
};

//Uniforms
uniform DirectionalLight directionalLight;
uniform sampler2D Diffuse;

uniform vec3 EyePos; //Where the camera is
uniform float SpecularIntensity;
uniform float SpecularExponent;

vec4 CalcLight(BaseLight Base, vec3 Direction, vec3 Normal)
{
	float DiffuseFactor = dot( -Direction ,Normal);
	vec4 DiffuseColour = vec4(0,0,0,0);
	vec4 SpecularColour = vec4(0,0,0,0);
	if(DiffuseFactor > 0)
	{
		DiffuseColour = vec4(Base.Colour, 1.0) * Base.Intensity * DiffuseFactor;
		
		vec3 DirectionToEye = normalize(EyePos - WorldPos0);
		vec3 ReflectDirection = normalize(reflect(Direction, Normal));
		
		float SpecularFactor = dot(DirectionToEye, ReflectDirection); //Gives cosine between
		SpecularFactor = pow(SpecularFactor, SpecularExponent);
		
		if(SpecularFactor > 0)
		{
			SpecularColour = vec4(Base.Colour, 1.0) * SpecularIntensity * SpecularFactor;
		}
	}
	return DiffuseColour + SpecularColour;
}

vec4 CalcDirectionalLight(DirectionalLight DirLight, vec3 Normal)
{
	return CalcLight(DirLight.Light, -DirLight.Direction, Normal);
}

void main()
{
	vec4 TotalLight = vec4(0, 0, 0, 1);
	vec4 TextureColour = texture2D(Diffuse, TexCoord0.xy);
	
	vec3 Norm = normalize(Normal0);
	
	TotalLight += CalcDirectionalLight(directionalLight, Norm);
	
	gl_FragColor = TextureColour * TotalLight;
}