#include "MainGame.h"

MainGame::MainGame(D3DEngine::Window* window, D3DEngine::Time* time)
{
	m_Window = window;
	m_Time = time;
	m_Input = new D3DEngine::Input(m_Window);

	D3DEngine::Vert* Vertices = new D3DEngine::Vert[4]
	{ 
		D3DEngine::Vert(D3DEngine::Vector3f(-1,-1,0)),
		D3DEngine::Vert(D3DEngine::Vector3f(0,1,0)),
		D3DEngine::Vert(D3DEngine::Vector3f(1,-1,0)),
		D3DEngine::Vert(D3DEngine::Vector3f(0,-1,1)),
	};
	
	int Indices[12] = { 0,1,3,3,1,2,2,1,0,0,2,3 };


	m_Mesh = D3DEngine::ResourceLoader::LoadMesh("./Models/box.obj");
	//m_Mesh = new D3DEngine::Mesh();
	//m_Mesh->AddVertices(Vertices,4, Indices, 12);

	m_Shader.AddVertexShader(D3DEngine::ResourceLoader::LoadShader("BasicVertex.vert"));
	m_Shader.AddFragmentShader(D3DEngine::ResourceLoader::LoadShader("BasicVertex.frag"));
	m_Shader.CompileShader();
	m_Shader.AddUniform("Transform");

	m_Transform.SetProjection(70.0f, m_Window->GetWidth(), m_Window->GetHeight(), 0.1f, 1000.0f);
	m_Transform.SetCamera(&m_Camera);
}

MainGame::~MainGame()
{
}

void MainGame::Input()
{
	m_Input->Update();
	//Do Camera
	m_Camera.DoInput(*m_Input, *m_Time);


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
	m_Transform.SetTranslation(0, 0, 5);
	m_Transform.SetRotation(TempAmount * 180, TempAmount * 180, TempAmount * 180);
	m_Transform.SetScaling(.4, .4, .4);
}

void MainGame::Draw()
{
	m_Shader.Bind();
	D3DEngine::Matrix4f Temp = m_Transform.GetTransformation();
	m_Shader.SetUniform("Transform", m_Transform.GetProjectedTransformation());
	m_Mesh->Draw();
}