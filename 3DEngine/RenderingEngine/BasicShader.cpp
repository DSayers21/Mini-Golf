#include "BasicShader.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	BasicShader::BasicShader()
	{
		AddVertexShaderFromFile("BasicShader.vert");
		AddFragmentShaderFromFile("BasicShader.frag");
		CompileShader();
		//Uniforms
		AddUniform("Transform");
		AddUniform("BaseColour");
	}

	BasicShader::~BasicShader()
	{
	}

	void BasicShader::UpdateUniforms(Transform* transform, Material material)
	{
		material.GetTexture()->Bind();

		Matrix4f WorldMatrix = transform->GetTransformation();
		Matrix4f ProjectedMatrix = GetRenderEngine()->GetCamera()->GetViewProjection().Mult(WorldMatrix);

		SetUniformM4("Transform", ProjectedMatrix);
		SetUniformV("BaseColour", *material.GetColour());
	}
}