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
		MeshRenderer(Mesh* mesh, Material* material);
		~MeshRenderer();
		void Input(float Delta);
		void Update(float Delta);
		void Draw(Shader* shader, RenderEngine* renderEngine);

	private:
		D3DEngine::Mesh* m_Mesh;
		D3DEngine::Material* m_Material;
	};
}