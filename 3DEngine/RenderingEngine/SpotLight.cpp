#include "SpotLight.h"

namespace D3DEngine
{
	SpotLight::SpotLight()
	{
		*this = SpotLight(PointLight(), Vector3f(0, 0, 0), 0);
	}

	SpotLight::SpotLight(PointLight pointLight, Vector3f direction, float cutoff)
	{
		m_PointLight = pointLight;
		m_Direction = direction.Normalise();
		m_Cutoff = cutoff;
	}


	SpotLight::~SpotLight()
	{
	}
}