#include "ForwardAmbient.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardAmbient::ForwardAmbient()
	{
		AddVertexShaderFromFile("Forward-Ambient.vert");
		AddFragmentShaderFromFile("Forward-Ambient.frag");

		//Set Attribs
		SetAttribLocation("Postion", 0);
		SetAttribLocation("TexCoord", 1);

		CompileShader();
		//Uniforms
		AddUniform("MVP");
		AddUniform("AmbientIntensity");
	}

	ForwardAmbient::~ForwardAmbient()
	{
	}

	void ForwardAmbient::UpdateUniforms(Transform* transform, Material material)
	{
		material.GetTexture()->Bind();

		Matrix4f WorldMatrix = transform->GetTransformation();
		Matrix4f ProjectedMatrix = GetRenderEngine()->GetCamera()->GetViewProjection().Mult(WorldMatrix);

		SetUniformM4("MVP", ProjectedMatrix);
		SetUniformV("AmbientIntensity", GetRenderEngine()->GetAmbientLight());
	}
}