#include "DirectionalLight.h"
#include "RenderEngine.h"
#include "ForwardDirectional.h"

namespace D3DEngine
{
	DirectionalLight::DirectionalLight()
	{
	}

	DirectionalLight::DirectionalLight(Vector3f Colour, float Intensity)
	{
		m_Colour = Colour;
		m_Intensity = Intensity;
		SetShader(new ForwardDirectional());
	}

	DirectionalLight::~DirectionalLight()
	{
	}
}