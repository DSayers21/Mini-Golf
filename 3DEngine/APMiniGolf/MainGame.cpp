#include "MainGame.h"

MainGame::MainGame(D3DEngine::Window* window)
{
	m_Window = window;
	m_Input = new D3DEngine::Input(m_Window);

	//m_Mesh.AddVertices(Data, 4, Indices, 12);
	m_Mesh = D3DEngine::ResourceLoader::LoadMesh("./Models/tri.obj");

	m_Shader.AddVertexShader(D3DEngine::ResourceLoader::LoadShader("BasicVertex.vert"));
	m_Shader.AddFragmentShader(D3DEngine::ResourceLoader::LoadShader("BasicVertex.frag"));
	m_Shader.CompileShader();
	m_Shader.AddUniform("Transform");
}

MainGame::~MainGame()
{
}

void MainGame::Input()
{
	m_Input->Update();
	int MX = (m_Input->GetMousePos().x);
	int MY = (m_Input->GetMousePos().y);
	if (m_Input->GetMouseDown(D3DEngine::MOUSE_LEFT_BUTTON))
	{
		std::cout << "Mouse Pressed Left at:: (" << MX << "," << MY << ")" << std::endl;
	}
}

void MainGame::Update()
{
	Temp += 0.0001f;
	float TempAmount = sin(Temp);
	m_Transform.SetTranslation(0, 0, 0);
	m_Transform.SetRotation(TempAmount * 180, 0, TempAmount*180);
	m_Transform.SetScaling(.4, .4, .4);
}

void MainGame::Draw()
{
	m_Shader.Bind();
	D3DEngine::Matrix4f Temp = m_Transform.GetTransformation();
	m_Shader.SetUniform("Transform", m_Transform.GetTransformation());
	m_Mesh->Draw();
}