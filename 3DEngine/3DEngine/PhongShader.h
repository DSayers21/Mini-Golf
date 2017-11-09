#pragma once
#include "Shader.h"
#include "Transform.h"

namespace D3DEngine
{
	class PhongShader : public Shader
	{
	public:
		PhongShader();
		~PhongShader();
		void UpdateUniforms(Matrix4f WorldMatrix, Matrix4f ProjectedMatrix, Material material);

		//Getters
		inline Vector3f GetAmbientLight() { return m_AmbientLight; }
		inline DirectionalLight GetDirectionalLight() { return m_DirectionalLight; }
		//Setters
		inline void SetAmbientLight(Vector3f ambientlight) { m_AmbientLight = ambientlight; }
		inline void SetDirectionalLight(DirectionalLight dirLight) { m_DirectionalLight = dirLight; }
		inline void SetTransform(Transform* Trans) { m_Transform = Trans; }
	private:
		Vector3f m_AmbientLight = Vector3f(0.1,0.1,0.1);
		DirectionalLight m_DirectionalLight;;
		Transform* m_Transform;
	};
}