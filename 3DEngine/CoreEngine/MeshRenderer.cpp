#include "MeshRenderer.h"

namespace D3DEngine
{
	MeshRenderer::MeshRenderer(D3DEngine::Mesh* mesh, D3DEngine::Material* material)
	{
		m_Mesh = mesh;
		m_Material = material;
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Input(float Delta)
	{
	}

	void MeshRenderer::Update(float Delta)
	{
	}

	void MeshRenderer::Draw(D3DEngine::Shader* shader)
	{
		shader->Bind();
		shader->UpdateUniforms(GetTransform(), m_Material);
		m_Mesh->Draw();
	}
}