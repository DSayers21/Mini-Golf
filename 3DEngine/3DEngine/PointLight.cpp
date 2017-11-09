#include "PointLight.h"

namespace D3DEngine
{
	PointLight::PointLight()
	{
		*this = PointLight(BaseLight(), Attenuation(), Vector3f(0,0,0), 0);
	}

	PointLight::PointLight(BaseLight& baseLight, Attenuation& attenuation, Vector3f& Position, float Range)
	{
		m_BaseLight = baseLight;
		m_Attenuation = attenuation;
		m_Position = Position;
		m_Range = Range;
	}

	PointLight::~PointLight()
	{
	}
}