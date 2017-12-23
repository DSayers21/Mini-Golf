#pragma once

//Includes
#include "Vector3f.h"
#include "GameComponent.h"
#include "Attenuation.h"
#include "ResourceManagement/ShaderList.h"
#include "Shader.h"

namespace D3DEngine
{
	//Inherits from GameComponent
	class BaseLight : public GameComponent
	{
	public:
		//Empty Constructor
		BaseLight() {}
		//Constructors
		BaseLight(ShaderList* shaderList);
		BaseLight(ShaderList* shaderList, Vector3f colour, float intensity);
		//Destructor
		virtual ~BaseLight();
		//Function to add light to the render engine
		void AddToEngine(MainComp * mainComp);
		//Calculate the range of the light
		float CalcRange();

		//Getters
		inline Vector3f GetColour() { return m_Colour; }
		inline float GetIntensity() { return m_Intensity; }
		inline Shader* GetShader() { return m_Shader; }
		inline Attenuation GetAttenuation() { return m_Attenuation; }
		inline float GetRange() { return m_Range; }
		Vector3f& GetDirection() { return GetTransform()->GetTransformedRot().GetForward(); }
		inline float& GetCutoff() { return m_Cutoff; }

		//Setters
		inline void SetColour(const Vector3f& colour) { m_Colour = colour; }
		inline void SetIntensity(float intensity) { m_Intensity = intensity; }
		inline void SetShader(Shader* shader) { m_Shader = shader; }
		inline void SetAttenuation(Attenuation& attenuation) { m_Attenuation = attenuation; }
		inline void SetRange(float& Range) { m_Range = Range; }
		inline void SetCutoff(float cutoff) { m_Cutoff = cutoff; }
		
	protected:
		//Pointer to the shader for the light
		Shader* m_Shader;
		Vector3f m_Colour;						//The colour of the light
		float m_Intensity;
		//Pointlight Extras
		Attenuation m_Attenuation;				//Attenuation of light
		float m_Range;							//Range of point light
		//Spot Extras	
		float m_Cutoff;							//Cutoff of where spotlight effects
		const static int COLOUR_DEPTH = 256;	//The colour depth
	};
}