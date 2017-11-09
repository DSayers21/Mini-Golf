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

		//Getters
		Vector3f GetAmbientLight() { return m_AmbientLight; }
		DirectionalLight GetDirectionalLight() { return m_DirectionalLight; }
		//Setters
		void SetAmbientLight(Vector3f ambientlight) { m_AmbientLight = ambientlight; }
		void SetDirectionalLight(DirectionalLight dirLight) { m_DirectionalLight = dirLight; }

	private:
		Vector3f m_AmbientLight = Vector3f(0.1,0.1,0.1);
		DirectionalLight m_DirectionalLight;;
	};
}