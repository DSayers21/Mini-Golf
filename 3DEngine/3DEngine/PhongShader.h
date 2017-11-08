#pragma once
#include "Shader.h"

namespace D3DEngine
{
	class PhongShader : public Shader
	{
	public:
		PhongShader();
		~PhongShader();
		void UpdateUniforms(Matrix4f WorldMatrix, Matrix4f ProjectedMatrix, Material material);



		//Getters And Setters
		Vector3f GetAmbientLight() { return m_AmbientLight; }
		void SetAmbientLight(Vector3f ambientlight) { m_AmbientLight = ambientlight; }
	private:
		Vector3f m_AmbientLight;
	};
}