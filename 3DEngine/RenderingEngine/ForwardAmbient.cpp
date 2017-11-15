#include "ForwardAmbient.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardAmbient::ForwardAmbient()
	{
		std::string VertexShaderText = LoadShader("Forward-Ambient.vert");
		std::string FragmentShaderText = LoadShader("Forward-Ambient.frag");

		AddVertexShader(VertexShaderText);
		AddFragmentShader(FragmentShaderText);

		//Set Attribs
		AddAllAttributes(VertexShaderText);

		CompileShader();

		//Uniforms
		AddAllUniforms(VertexShaderText);
		AddAllUniforms(FragmentShaderText);
	}

	ForwardAmbient::~ForwardAmbient()
	{
	}

	void ForwardAmbient::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		material->GetTexture("Diffuse")->Bind();
		Matrix4f WorldMatrix = transform->GetTransformation();
		Matrix4f ProjectedMatrix = renderEngine->GetCamera()->GetViewProjection().Mult(WorldMatrix);

		SetUniformM4("MVP", ProjectedMatrix);
		SetUniformV("AmbientIntensity", renderEngine->GetAmbientLight());
	}
}