#include "DirectionalLight.h"

namespace D3DEngine
{
	DirectionalLight::DirectionalLight(BaseLight base, Vector3f direction)
	{
		m_Base = base;
		m_Direction = direction;
	}

	DirectionalLight::~DirectionalLight()
	{
	}
}