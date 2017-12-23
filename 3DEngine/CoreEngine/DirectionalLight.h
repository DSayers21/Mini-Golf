#pragma once

//Includes
#include "BaseLight.h"
#include "Vector3f.h"

namespace D3DEngine
{
	//Inherits from BaseLight
	class DirectionalLight : public BaseLight
	{
	public:
		//Constructor
		DirectionalLight(ShaderList* shaderList);
		DirectionalLight(ShaderList* shaderList, Vector3f Colour, float Intensity);
		//Destructor
		virtual ~DirectionalLight();
	};
}