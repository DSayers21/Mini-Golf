#include "BaseLight.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	BaseLight::BaseLight()
	{
		*this = BaseLight(Vector3f(0, 0, 0), 0);
	}

	BaseLight::BaseLight(Vector3f colour, float intensity)
	{
		m_Colour = colour;
		m_Intensity = intensity;
	}

	BaseLight::~BaseLight()
	{
	}

	void BaseLight::AddToRenderingEngine(RenderEngine * renderEngine)
	{
		renderEngine->AddLight(this);
	}

	float BaseLight::CalcRange()
	{
		//CalcRange
		float a = m_Attenuation.GetExponent();
		float b = m_Attenuation.GetLinear();
		float c = m_Attenuation.GetConstant();
		c -= COLOUR_DEPTH * (GetIntensity() * GetColour().Max());	//Subtract the max amount of colour depth

		float Range = (-b + sqrtf(b*b - 4 * a * c)) / (2 * a);

		return Range;
	}
}