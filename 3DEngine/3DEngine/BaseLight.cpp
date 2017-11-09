#include "BaseLight.h"

namespace D3DEngine
{
	BaseLight::BaseLight(Vector3f colour, float intensity)
	{
		m_Colour = colour;
		m_Intensity = intensity;
	}


	BaseLight::~BaseLight()
	{
	}
}