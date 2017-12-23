//Includes
#include "DirectionalLight.h"

namespace D3DEngine
{
	DirectionalLight::DirectionalLight(ShaderList* shaderList)
	{
		//Empty
	}

	DirectionalLight::DirectionalLight(ShaderList* shaderList, Vector3f Colour, float Intensity)
	{
		m_Colour = Colour;			//Set the colour of the light
		m_Intensity = Intensity;	//Set the intensity of the light
		//Set the shader to use to render the light
		SetShader(new Shader("Forward-Directional", shaderList));
	}

	DirectionalLight::~DirectionalLight()
	{
		//Display Message
		std::cerr << "Destructor: DLight Component" << std::endl;
	}
}