#include "TestGame.h"
#include "Quaternion.h"
#include "MathBasics.h"

TestGame::TestGame()
{

}

TestGame::~TestGame()
{

}

void TestGame::Init()
{
	float FieldDepth = 10.0f;
	float FieldWidth = 10.0f;

	D3DEngine::Vert Vertices[] = {
		D3DEngine::Vert(D3DEngine::Vector3f(-FieldWidth, 0.0f, -FieldDepth), D3DEngine::Vector2f(0.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(-FieldWidth, 0.0f, FieldDepth * 3), D3DEngine::Vector2f(0.0f,1.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(FieldWidth * 3, 0.0f, -FieldDepth), D3DEngine::Vector2f(1.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(FieldWidth * 3, 0.0f, FieldDepth * 3), D3DEngine::Vector2f(1.0f,1.0f)),
	};
	int Indices[] = { 0, 1, 2 ,2, 1, 3 };
	D3DEngine::Mesh* mesh = new D3DEngine::Mesh(Vertices, 4, Indices, 6, true);
	D3DEngine::Vert Vertices2[] = {
		D3DEngine::Vert(D3DEngine::Vector3f(-FieldWidth / 10, 0.0f, -FieldDepth / 10), D3DEngine::Vector2f(0.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(-FieldWidth/10, 0.0f, FieldDepth / 10 * 3), D3DEngine::Vector2f(0.0f,1.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(FieldWidth / 10 * 3, 0.0f, -FieldDepth / 10), D3DEngine::Vector2f(1.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(FieldWidth / 10 * 3, 0.0f, FieldDepth / 10 * 3), D3DEngine::Vector2f(1.0f,1.0f)),
	};
	int Indices2[] = { 0, 1, 2 ,2, 1, 3 };
	D3DEngine::Mesh* mesh2 = new D3DEngine::Mesh(Vertices2, 4, Indices2, 6, true);
	
	D3DEngine::Material* material = new D3DEngine::Material();
	material->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Test.png"));
	material->AddFloat("SpecularIntensity", 1);
	material->AddFloat("SpecularExponent", 8);

	D3DEngine::GameObject* PlaneObject = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* meshRenderer = new D3DEngine::MeshRenderer(mesh, material);
	PlaneObject->AddComponent(meshRenderer);
	PlaneObject->GetTransform()->GetPosition()->Set(-2, -1, 5);

	D3DEngine::GameObject* DirectionalLightObject = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight = new D3DEngine::DirectionalLight(D3DEngine::Vector3f(0,0,1), 0.9f);
	DirectionalLightObject->AddComponent(directionalLight);
	DirectionalLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(-15.0f)));


	D3DEngine::GameObject* PointLightObject = new D3DEngine::GameObject();
	PointLightObject->AddComponent(new D3DEngine::PointLight(D3DEngine::Vector3f(0, 1, 0), 0.9f, D3DEngine::Attenuation(0, 0, 1)));
	PointLightObject->GetTransform()->GetPosition()->Set(6, 0,12);

	D3DEngine::GameObject* SpotLightObject = new D3DEngine::GameObject();
	SpotLightObject->AddComponent(new D3DEngine::SpotLight(D3DEngine::Vector3f(0, 1, 1),12.0f, 
		D3DEngine::Attenuation(0, 0, 1), 0.7));
	SpotLightObject->GetTransform()->GetPosition()->Set(5, 0, 5);
	SpotLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(90.0f)));

	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	CameraObject->AddComponent(new D3DEngine::Camera(TO_RADIANS(70.0f), 800/600, 0.01f, 1000.0f));

	D3DEngine::MeshRenderer* meshRenderer2 = new D3DEngine::MeshRenderer(mesh2, material);

	D3DEngine::GameObject* testMesh1 = new D3DEngine::GameObject();
	testMesh1->AddComponent(meshRenderer2);
	testMesh1->GetTransform()->GetPosition()->Set(0,4,6);
	testMesh1->GetTransform()->SetRotation(new D3DEngine::Quaternion(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(-55)));

	D3DEngine::GameObject* testMesh2 = new D3DEngine::GameObject();
	testMesh2->AddComponent(new D3DEngine::MeshRenderer(mesh2, material));
	testMesh2->GetTransform()->GetPosition()->Set(0, 3, 5);

	D3DEngine::GameObject* testMesh3 = new D3DEngine::GameObject();
	testMesh3->AddComponent(new D3DEngine::MeshRenderer(mesh2, material));
	testMesh3->GetTransform()->GetPosition()->Set(0, 5, 7);
	

	//testMesh3->AddChild(CameraObject);
	//testMesh2->AddChild(testMesh3);
	testMesh1->AddChild(testMesh2);
	testMesh1->AddChild(CameraObject);

	AddObject(PlaneObject);
	AddObject(DirectionalLightObject);
	AddObject(PointLightObject);
	AddObject(SpotLightObject);
	AddObject(testMesh1);

}

void TestGame::Input(D3DEngine::GetInput* input, float Delta)
{
	input->Update();

	int MX = input->GetMousePos().GetX();
	int MY = (input->GetMousePos().GetY());
	if (input->GetMouseDown(D3DEngine::MOUSE_LEFT_BUTTON))
	{
		std::cout << "Mouse Pressed Left at:: (" << MX << "," << MY << ")" << std::endl;
	}
	m_RootObject->Input(input, Delta);
}