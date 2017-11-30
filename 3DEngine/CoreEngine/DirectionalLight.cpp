#include "DirectionalLight.h"

namespace D3DEngine
{
	DirectionalLight::DirectionalLight(ShaderList* shaderList)
	{
	}

	DirectionalLight::DirectionalLight(ShaderList* shaderList, Vector3f Colour, float Intensity)
	{
		m_Colour = Colour;
		m_Intensity = Intensity;
		SetShader(new Shader("Forward-Directional", shaderList));
	}

	DirectionalLight::~DirectionalLight()
	{
	}
}