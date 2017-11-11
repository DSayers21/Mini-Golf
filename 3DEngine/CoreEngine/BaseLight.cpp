#include "BaseLight.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	BaseLight::BaseLight()
	{
		*this = BaseLight(Vector3f(0, 0, 0), 0);
	}

	BaseLight::BaseLight(Vector3f colour, float intensity)
	{
		m_Colour = colour;
		m_Intensity = intensity;
	}

	BaseLight::~BaseLight()
	{
	}

	void BaseLight::AddToRenderingEngine(RenderEngine * renderEngine)
	{
		renderEngine->AddLight(this);
	}
}