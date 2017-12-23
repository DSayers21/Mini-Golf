#pragma once

//Includes
#include "GameComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Shader.h"
#include <iostream>

namespace D3DEngine
{
	//Inherits from GameComponent
	class MeshRenderer : public GameComponent
	{
	public:
		//Constructor
		MeshRenderer(Mesh* mesh, Material* material);
		//Destructor
		~MeshRenderer();
		//Function to render the mesh to the screen
		void Draw(Shader* shader, RenderEngine* renderEngine);

	private:
		//Pointer to the mesh
		D3DEngine::Mesh* m_Mesh;
		//Pointer to the material to be drawn on the mesh
		D3DEngine::Material* m_Material;
	};
}