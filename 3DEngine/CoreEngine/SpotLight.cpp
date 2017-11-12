#include "SpotLight.h"
#include "ForwardSpot.h"

namespace D3DEngine
{
	SpotLight::SpotLight()
	{
		*this = SpotLight(Vector3f(0,1,0), 1, Attenuation(0,0,0), Vector3f(1, 1, 1), 0);
	}

	SpotLight::SpotLight(Vector3f colour, float intensity, Attenuation& attenuation, Vector3f direction, float cutoff)
	{
		m_Colour = colour;
		m_Intensity = intensity;
		m_Attenuation = attenuation;
		m_Range = CalcRange();

		m_Direction = direction.Normalise();
		m_Cutoff = cutoff;

		SetShader(new ForwardSpot());
	}

	SpotLight::~SpotLight()
	{
	}
}