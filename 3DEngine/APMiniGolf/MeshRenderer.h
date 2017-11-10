#pragma once
#include "GameComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "BasicShader.h"

class MeshRenderer : public D3DEngine::GameComponent
{
public:
	MeshRenderer(D3DEngine::Mesh* mesh, D3DEngine::Material* material);
	~MeshRenderer();

	void Draw(D3DEngine::Transform* transform);

private:
	D3DEngine::Mesh* m_Mesh;
	D3DEngine::Material* m_Material;

	D3DEngine::BasicShader* m_Shader = new D3DEngine::BasicShader();
};