#include "DirectionalLight.h"
#include "RenderEngine.h"
#include "ForwardDirectional.h"

namespace D3DEngine
{
	DirectionalLight::DirectionalLight()
	{
	}

	DirectionalLight::DirectionalLight(Vector3f Colour, float Intensity, Vector3f Direction)
	{
		m_Colour = Colour;
		m_Intensity = Intensity;
		m_Direction = Direction.Normalise();
		SetShader(new ForwardDirectional());
	}

	DirectionalLight::~DirectionalLight()
	{
	}
}