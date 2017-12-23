//Includes
#include "MeshRenderer.h"

namespace D3DEngine
{
	MeshRenderer::MeshRenderer(D3DEngine::Mesh* mesh, D3DEngine::Material* material) :
		m_Mesh(mesh), m_Material(material)
	{
		//Empty
	}

	MeshRenderer::~MeshRenderer()
	{
		//Display Message
		std::cerr << "Destructor: Mesh Renderer Component" << std::endl;
		//Delete the mesh
		delete m_Mesh;
		//Set to nullptr
		m_Material = nullptr;
	}

	void MeshRenderer::Draw(D3DEngine::Shader* shader, RenderEngine* renderEngine)
	{
		//Bind to the current shader
		shader->Bind();
		//Update the shader to represent the object being drawn
		shader->UpdateUniforms(GetTransform(), m_Material, renderEngine);
		//Render the mesh
		m_Mesh->Draw();
	}
}