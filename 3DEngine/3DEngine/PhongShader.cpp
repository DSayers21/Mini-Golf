#include "PhongShader.h"

namespace D3DEngine
{
	PhongShader::PhongShader()
	{
		m_DirectionalLight = DirectionalLight(BaseLight(Vector3f(1, 1, 1), .1), Vector3f(1, 1, 1));

		AddVertexShader(D3DEngine::ResourceLoader::LoadShader("PhongShader.vert"));
		AddFragmentShader(D3DEngine::ResourceLoader::LoadShader("PhongShader.frag"));
		CompileShader();
		//Uniforms
		AddUniform("Transform");
		AddUniform("TransformProjected");

		AddUniform("BaseColour");

		AddUniform("AmbientLight");

		AddUniform("directionalLight.Light.Colour");
		AddUniform("directionalLight.Light.Intensity");
		AddUniform("directionalLight.Direction");

		AddUniform("SpecularIntensity");
		AddUniform("SpecularExponent");
		AddUniform("EyePos");
	}

	PhongShader::~PhongShader()
	{
	}

	void PhongShader::UpdateUniforms(Matrix4f WorldMatrix, Matrix4f ProjectedMatrix, Material material)
	{
		if (material.GetTexture() != NULL)
			material.GetTexture()->Bind();
		else
			RenderUtil::UnBindTextures();

		SetUniformM4("Transform", WorldMatrix);
		SetUniformM4("TransformProjected", ProjectedMatrix);
		SetUniformV("BaseColour", *material.GetColour());
		//Lighting
		SetUniformV("AmbientLight", m_AmbientLight);
		SetUniformDL("directionalLight", m_DirectionalLight);
		//Specular Reflection
		SetUniformF("SpecularIntensity", material.GetSpecularIntensity());
		SetUniformF("SpecularExponent", material.GetSpecularExponent());
		SetUniformV("EyePos", m_Transform->GetCamera()->GetPos());
	}
}