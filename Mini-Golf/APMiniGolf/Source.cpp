//Open GL includes
#include <GL/glew.h>
#include <glm/glm.hpp>
//Includes
#include <iostream>
#include <string>
//My Includes
#include <Window.h>
#include <Mesh.h>
#include <Texture.h>
#include <Shader.h>
#include <Transform.h>
#include <Camera.h>

#ifdef _WIN32
#undef main
#endif

int main(int argc, char** argv)
{
	D3DEngine::Window m_Window;
	std::string Title = "Hello";
	m_Window.Init(Title, 800, 600);

	//
	D3DEngine::Vertex Vertices[] = {
		D3DEngine::Vertex(glm::vec3(-0.5f,-0.5f,0.0f), glm::vec2(0.0f,0.0f)),
		D3DEngine::Vertex(glm::vec3(0.0f,0.5f,0.0f), glm::vec2(0.5f,1.0f)),
		D3DEngine::Vertex(glm::vec3(0.5f,-0.5f,0.0f), glm::vec2(1.0f,0.0f)),
	};
	D3DEngine::Mesh m_Mesh(Vertices, sizeof(Vertices) / sizeof(Vertices[0]));
	D3DEngine::Shader m_Shader("./Shaders/ColourShading");
	D3DEngine::Texture m_Texture("./Textures/Bricks.jpg");
	D3DEngine::Transform m_Transform;
	D3DEngine::Camera m_Camera(glm::vec3(0,0,-10), 70.0f, (float)m_Window.GetWidth()/(float)m_Window.GetHeight(), 0.01f, 1000.0f);

	float Counter = 0.0f;

	while (!m_Window.IsClosed())
	{
		glLoadIdentity();
		glTranslatef(-1.5f, 0.0f, -6.0f);
		m_Window.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float cosCounter = cosf(Counter);
		m_Transform.GetPos().x = sinf(Counter);
		m_Transform.GetRot().z = Counter * 6;
		m_Transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		m_Shader.Bind();
		m_Texture.Bind(0);

		m_Shader.Update(m_Transform, m_Camera);
		
		m_Mesh.Draw();

		m_Window.Update();
		Counter += 0.0001f;
	}
	return 0;
}