#include "ForwardDirectional.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardDirectional::ForwardDirectional()
	{
		InitShader("Forward-Directional");
	}

	ForwardDirectional::~ForwardDirectional()
	{
	}

	void ForwardDirectional::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		material->GetTexture("Diffuse")->Bind();

		Matrix4f WorldMatrix = transform->GetTransformation();
		Matrix4f ProjectedMatrix = renderEngine->GetCamera()->GetViewProjection().Mult(WorldMatrix);

		SetUniformM4("Model", WorldMatrix);
		SetUniformM4("MVP", ProjectedMatrix);
		//Specular Reflection
		SetUniformF("SpecularIntensity", material->GetFloat("SpecularIntensity"));
		SetUniformF("SpecularExponent", material->GetFloat("SpecularExponent"));
		SetUniformV("EyePos", renderEngine->GetCamera()->GetTransform()->GetTransformedPos());
		//Directional Light
		SetUniformDL("directionalLight", renderEngine->GetActiveLight());
	}

	void ForwardDirectional::SetUniformDL(std::string UniformName, BaseLight* DirLight)
	{
		SetUniformBL(UniformName + ".Light", DirLight);
		SetUniformV(UniformName + ".Direction", DirLight->GetDirection());
	}

}