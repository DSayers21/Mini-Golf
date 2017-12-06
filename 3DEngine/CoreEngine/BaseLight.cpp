#include "BaseLight.h"
#include "RenderEngine.h"
#include "MainComp.h"

namespace D3DEngine
{
	BaseLight::BaseLight(ShaderList* shaderList)
	{
		*this = BaseLight(shaderList, Vector3f(0, 0, 0), 0);
	}

	BaseLight::BaseLight(ShaderList* shaderList, Vector3f colour, float intensity)
	{
		m_Colour = colour;
		m_Intensity = intensity;
	}

	BaseLight::~BaseLight()
	{
		std::cerr << "Destructor: BLight Component" << std::endl;

		//delete m_Shader;
	}

	void BaseLight::AddToEngine(MainComp * mainComp)
	{
		mainComp->GetRenderEngine()->AddLight(this);
	}

	float BaseLight::CalcRange()
	{
		//CalcRange
		float a = m_Attenuation.GetExponent();
		float b = m_Attenuation.GetLinear();
		float c = m_Attenuation.GetConstant();
		c -= COLOUR_DEPTH * (GetIntensity() * GetColour().Max());	//Subtract the max amount of colour depth

		float Range = (-b + sqrtf(b*b - 4 * a * c)) / (2 * a);

		return Range;
	}
}