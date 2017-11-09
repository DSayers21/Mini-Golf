#include "PointLight.h"

namespace D3DEngine
{
	PointLight::PointLight()
	{
	}

	PointLight::PointLight(BaseLight& baseLight, Attenuation& attenuation, Vector3f& Position)
	{
		m_BaseLight = baseLight;
		m_Attenuation = attenuation;
		m_Position = Position;
	}

	PointLight::~PointLight()
	{
	}
}