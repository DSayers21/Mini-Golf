#include "PointLight.h"
#include "RenderEngine.h"
#include "ForwardPoint.h"

namespace D3DEngine
{
	PointLight::PointLight()
	{
		*this = PointLight(Vector3f(0,0,0), 1, Attenuation());
	}

	PointLight::PointLight(Vector3f colour, float intensity, Attenuation& attenuation)
	{
		m_Colour = colour;
		m_Intensity = intensity;
		m_Attenuation = attenuation;

		m_Range = CalcRange();
	
		SetShader(new ForwardPoint());
	}

	PointLight::~PointLight()
	{
	}
}