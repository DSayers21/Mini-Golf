#version 330

const int MAX_POINT_LIGHTS = 4;

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

//How long light lasts, fading out from point
struct Attenuation {
	float Constant;
	float Linear;
	float Exponent;
};

struct PointLight {
	BaseLight Light;
	Attenuation Atten;
	vec3 Position;
	float Range; //Max Distance a pixel can be from point light and still be affected
};

//Uniforms
uniform vec3 BaseColour;
uniform vec3 AmbientLight;
uniform DirectionalLight directionalLight;
uniform PointLight PointLights[MAX_POINT_LIGHTS];
uniform sampler2D Sampler;

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

vec4 CalcPointLight(PointLight pointLight, vec3 Normal)
{
	vec3 LightDirection = WorldPos0 - pointLight.Position;
	float DistanceToPLight = length(LightDirection);
	
	if(DistanceToPLight > pointLight.Range)
		return vec4(0,0,0,0);
		
	LightDirection = normalize(LightDirection);
	//Get Colour From Light
	vec4 Colour = CalcLight(pointLight.Light, LightDirection, Normal);
	
	//Apply Attenuation, gets larger as the distance increases
	float Attenuation = pointLight.Atten.Constant + 
						pointLight.Atten.Linear * DistanceToPLight + 
						pointLight.Atten.Exponent * DistanceToPLight * DistanceToPLight +
						0.0001f; //Add small value to circumvent divide by zero
	
	return Colour / Attenuation;
}

void main()
{
	vec4 TotalLight = vec4(AmbientLight, 1);
	vec4 Colour = vec4(BaseColour, 1);
	vec4 TextureColour = texture2D(Sampler, TexCoord0.xy);
	
	if(Colour == vec4(0,0,0,1))
		Colour = TextureColour;
	
	if(TextureColour != vec4(0,0,0,0))
		Colour *= TextureColour;
	
	vec3 Norm = normalize(Normal0);
	
	TotalLight += CalcDirectionalLight(directionalLight, Norm);

	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		if(PointLights[i].Light.Intensity > 0)
			if(PointLights[i].Light.Intensity > 0)
				TotalLight += CalcPointLight(PointLights[i], Norm);
	}

	gl_FragColor = Colour * TotalLight;
}