#include "MeshRenderer.h"



MeshRenderer::MeshRenderer(D3DEngine::Mesh* mesh, D3DEngine::Material* material)
{
	m_Mesh = mesh;
	m_Material = material;
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Draw(D3DEngine::Transform* transform)
{
	m_Shader->Bind();
	m_Shader->UpdateUniforms(transform->GetTransformation(), transform->GetProjectedTransformation(), *m_Material);
	m_Mesh->Draw();
}