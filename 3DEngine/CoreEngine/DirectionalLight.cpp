#include "DirectionalLight.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	DirectionalLight::DirectionalLight()
	{
	}
	DirectionalLight::DirectionalLight(BaseLight base, Vector3f direction)
	{
		m_Base = base;
		m_Direction = direction.Normalise();
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::AddToRenderingEngine(RenderEngine * renderEngine)
	{
		renderEngine->AddDirectionalLight(this);
	}
}