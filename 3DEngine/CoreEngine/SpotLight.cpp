#include "SpotLight.h"

namespace D3DEngine
{
	SpotLight::SpotLight(ShaderList* shaderList)
	{
		*this = SpotLight(shaderList, Vector3f(0,1,0), 1, Attenuation(0,0,0), 0);
	}

	SpotLight::SpotLight(ShaderList* shaderList, Vector3f colour, float intensity, Attenuation& attenuation, float cutoff)
	{
		m_Colour = colour;
		m_Intensity = intensity;
		m_Attenuation = attenuation;
		m_Range = CalcRange();
		m_Cutoff = cutoff;

		SetShader(new Shader("Forward-Spot", shaderList));
	}

	SpotLight::~SpotLight()
	{
	}
}