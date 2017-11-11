#pragma once
#include "GameComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Shader.h"
#include <iostream>

class MeshRenderer : public D3DEngine::GameComponent
{
public:
	MeshRenderer(D3DEngine::Mesh* mesh, D3DEngine::Material* material);
	~MeshRenderer();
	void Input(D3DEngine::Transform* transform, float Delta);
	void Update(D3DEngine::Transform* transform, float Delta);
	void Draw(D3DEngine::Transform* transform, D3DEngine::Shader* shader);

private:
	D3DEngine::Mesh* m_Mesh;
	D3DEngine::Material* m_Material;
};