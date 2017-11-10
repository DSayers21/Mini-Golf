#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(D3DEngine::Mesh* mesh, D3DEngine::Material* material)
{
	m_Mesh = mesh;
	m_Material = material;
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Draw(D3DEngine::Transform* transform, D3DEngine::Shader* shader)
{
	shader->Bind();
	shader->UpdateUniforms(transform->GetTransformation(), transform->GetProjectedTransformation(), *m_Material);
	m_Mesh->Draw();
}