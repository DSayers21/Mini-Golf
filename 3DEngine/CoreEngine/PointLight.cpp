#include "PointLight.h"
#include "RenderEngine.h"
#include "ForwardPoint.h"

namespace D3DEngine
{
	PointLight::PointLight()
	{
		*this = PointLight(Vector3f(0,0,0), 1, Attenuation(), Vector3f(0,0,0), 0);
	}

	PointLight::PointLight(Vector3f colour, float intensity, Attenuation& attenuation, Vector3f& Position, float Range)
	{
		m_Colour = colour;
		m_Intensity = intensity;
		m_Attenuation = attenuation;
		m_Position = Position;
		m_Range = Range;

		SetShader(new ForwardPoint());
	}

	PointLight::~PointLight()
	{
	}
}