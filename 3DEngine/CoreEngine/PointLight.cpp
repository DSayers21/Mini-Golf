#include "PointLight.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	PointLight::PointLight(ShaderList* shaderList)
	{
		*this = PointLight(shaderList, Vector3f(0,0,0), 1, Attenuation());
	}

	PointLight::PointLight(ShaderList* shaderList, Vector3f colour, float intensity, Attenuation& attenuation)
	{
		m_Colour = colour;
		m_Intensity = intensity;
		m_Attenuation = attenuation;

		m_Range = CalcRange();
	
		SetShader(new Shader("Forward-Point", shaderList));
	}

	PointLight::~PointLight()
	{
	}
}