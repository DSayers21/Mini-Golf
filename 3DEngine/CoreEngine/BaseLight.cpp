//Includes
#include "BaseLight.h"
#include "RenderEngine.h"
#include "MainComp.h"

namespace D3DEngine
{
	BaseLight::BaseLight(ShaderList* shaderList)
	{
		//Runs different constructor with basic values
		*this = BaseLight(shaderList, Vector3f(0, 0, 0), 0);
	}

	BaseLight::BaseLight(ShaderList* shaderList, Vector3f colour, float intensity) :
		m_Colour(colour), m_Intensity(intensity)
	{
		//Empty
	}

	BaseLight::~BaseLight()
	{
		//Display Message
		std::cerr << "Destructor: BLight Component" << std::endl; 
		//Delete the shader
		delete m_Shader;
	}

	void BaseLight::AddToEngine(MainComp * mainComp)
	{
		//Add the light to the render engine
		mainComp->GetRenderEngine()->AddLight(this);
	}

	float BaseLight::CalcRange()
	{
		//Calculate the Range
		float a = m_Attenuation.GetExponent();
		float b = m_Attenuation.GetLinear();
		float c = m_Attenuation.GetConstant();
		c -= COLOUR_DEPTH * (GetIntensity() * GetColour().Max());	//Subtract the max amount of colour depth
		//Get the range
		float Range = (-b + sqrtf(b*b - 4 * a * c)) / (2 * a);
		//Return the caluclated range
		return Range;
	}
}