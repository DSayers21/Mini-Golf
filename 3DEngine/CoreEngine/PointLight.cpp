//Includes
#include "PointLight.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	PointLight::PointLight(ShaderList* shaderList)
	{
		//Run second constructor with basic values
		*this = PointLight(shaderList, Vector3f(0,0,0), 1, Attenuation());
	}

	PointLight::PointLight(ShaderList* shaderList, Vector3f colour, float intensity, Attenuation& attenuation)
	{
		m_Colour = colour;				//Set the colour
		m_Intensity = intensity;		//Set the intensity
		m_Attenuation = attenuation;	//Set the attenuation

		m_Range = CalcRange();			//Calculate the range of the light
		//Set the shader
		SetShader(new Shader("Forward-Point", shaderList));
	}

	PointLight::~PointLight()
	{
		//Empty
	}
}