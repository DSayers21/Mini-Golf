#include "PhongShader.h"

namespace D3DEngine
{
	PhongShader::PhongShader()
	{
		m_DirectionalLight = DirectionalLight(BaseLight(Vector3f(1, 0, 0), .2), Vector3f(0, 1, 0));

		AddVertexShader(D3DEngine::ResourceLoader::LoadShader("PhongShader.vert"));
		AddFragmentShader(D3DEngine::ResourceLoader::LoadShader("PhongShader.frag"));
		CompileShader();
		//Uniforms
		AddUniform("Transform");
		AddUniform("BaseColour");

		AddUniform("AmbientLight");

		AddUniform("directionalLight.Light.Colour");
		AddUniform("directionalLight.Light.Intensity");
		AddUniform("directionalLight.Direction");
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

		SetUniformM4("Transform", ProjectedMatrix);
		SetUniformV("BaseColour", *material.GetColour());
		SetUniformV("AmbientLight", m_AmbientLight);
		SetUniformDL("directionalLight", m_DirectionalLight);
	}
}