#include "SpotLight.h"

namespace D3DEngine
{
	SpotLight::SpotLight(ShaderList* shaderList)
	{
		//Run second constructor with basic values
		*this = SpotLight(shaderList, Vector3f(0,1,0), 1, Attenuation(0,0,0), 0);
	}

	SpotLight::SpotLight(ShaderList* shaderList, Vector3f colour, float intensity, Attenuation& attenuation, float cutoff)
	{
		m_Colour = colour;					//Set the colour
		m_Intensity = intensity;			//Set the intensity
		m_Attenuation = attenuation;		//Set the attenuation
		m_Range = CalcRange();				//Calculate the range of the light
		m_Cutoff = cutoff;					//Set the cufoff of the light
		//Set the shader for the light
		SetShader(new Shader("Forward-Spot", shaderList));
	}

	SpotLight::~SpotLight()
	{
		//Empty
	}
}