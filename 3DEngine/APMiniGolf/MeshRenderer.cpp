#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(D3DEngine::Mesh* mesh, D3DEngine::Material* material)
{
	m_Mesh = mesh;
	m_Material = material;
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Input(D3DEngine::Transform * transform, float Delta)
{
}

void MeshRenderer::Update(D3DEngine::Transform * transform, float Delta)
{
}

void MeshRenderer::Draw(D3DEngine::Transform* transform, D3DEngine::Shader* shader)
{
	shader->Bind();
	shader->UpdateUniforms(*transform, *m_Material);
	m_Mesh->Draw();
}