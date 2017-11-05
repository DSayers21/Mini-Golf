#include "MainGame.h"

MainGame::MainGame(D3DEngine::Window* window)
{
	m_Window = window;
	m_Input = new D3DEngine::Input(m_Window);

	D3DEngine::Vert Data[] = { 
		D3DEngine::Vert(D3DEngine::Vector3f(-1,-1,0)),
		D3DEngine::Vert(D3DEngine::Vector3f(0,1,0)),
		D3DEngine::Vert(D3DEngine::Vector3f(1,-1,0)),
	};

	m_Mesh.AddVertices(Data, 3);
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
	m_Transform.SetTranslation(TempAmount, 0, 0);
}

void MainGame::Draw()
{
	m_Shader.Bind();
	m_Shader.SetUniform("Transform", m_Transform.GetTransformation());
	m_Mesh.Draw();
}
