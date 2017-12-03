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
		std::cerr << "Destructor: Mesh Renderer Component" << std::endl;
		delete m_Mesh;
		//delete m_Material;
	}

	void MeshRenderer::Input(float Delta)
	{
	}

	void MeshRenderer::Update(float Delta)
	{
	}

	void MeshRenderer::Draw(D3DEngine::Shader* shader, RenderEngine* renderEngine)
	{
		shader->Bind();
		//std::cerr << GetTransform()->GetPosition()->ToString() << std::endl;
		shader->UpdateUniforms(GetTransform(), m_Material, renderEngine);
		m_Mesh->Draw();
	}
}