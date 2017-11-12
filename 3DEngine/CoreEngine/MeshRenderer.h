#pragma once
#include "GameComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Shader.h"
#include <iostream>

namespace D3DEngine
{
	class MeshRenderer : public GameComponent
	{
	public:
		MeshRenderer(D3DEngine::Mesh* mesh, D3DEngine::Material* material);
		~MeshRenderer();
		void Input(float Delta);
		void Update(float Delta);
		void Draw(D3DEngine::Shader* shader);

	private:
		D3DEngine::Mesh* m_Mesh;
		D3DEngine::Material* m_Material;
	};
}