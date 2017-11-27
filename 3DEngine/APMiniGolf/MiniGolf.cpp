#include "MiniGolf.h"

#include "DirectionalLight.h"
#include "GolfClub.h"

MiniGolf::MiniGolf()
{
}


MiniGolf::~MiniGolf()
{
}

void MiniGolf::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
{
	D3DEngine::PhysicsEngineComponent* m_PhysicsEngineComponent = new D3DEngine::PhysicsEngineComponent(physicsEngine);

	physicsEngine->AddObject(D3DEngine::PhysicsObject(new D3DEngine::BoundingSphere(D3DEngine::Vector3f(0.0f, 0.0f, 0.0f), .2f), D3DEngine::Vector3f(0.0f, 0.0f, 0.0f)));

	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	float Aspect = m_Window->GetWidth() / m_Window->GetHeight();
	CameraObject->AddComponent(new D3DEngine::Camera(TO_RADIANS(90.0f), Aspect, 0.01f, 1000.0f));
	CameraObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(180.0f)));
	CameraObject->GetTransform()->SetPosition(D3DEngine::Vector3f(0.0f, 2.0f, 2.0f));
	CameraObject->AddComponent(new D3DEngine::FreeLook());

	//MaterialOne
	D3DEngine::Material* material = new D3DEngine::Material();
	material->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/GolfTexture.png"));
	material->AddFloat("SpecularIntensity", 1);
	material->AddFloat("SpecularExponent", 8);

	D3DEngine::Material* GolfBallMat = new D3DEngine::Material();
	GolfBallMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/GolfBallTexture.png"));
	GolfBallMat->AddFloat("SpecularIntensity", 1);
	GolfBallMat->AddFloat("SpecularExponent", 8);

	D3DEngine::Material* SideMat = new D3DEngine::Material();
	SideMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Wood.png"));
	SideMat->AddFloat("SpecularIntensity", 1);
	SideMat->AddFloat("SpecularExponent", 8);

	D3DEngine::Material* MetalMat = new D3DEngine::Material();
	MetalMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Metal.png"));
	MetalMat->AddFloat("SpecularIntensity", 1);
	MetalMat->AddFloat("SpecularExponent", 8);

	D3DEngine::Mesh* BallMesh = new D3DEngine::Mesh("./Models/Ball.obj", m_MeshList);
	D3DEngine::Mesh* BackMesh = new D3DEngine::Mesh("./Models/CourseBack.obj", m_MeshList);
	D3DEngine::Mesh* SideMesh = new D3DEngine::Mesh("./Models/CourseSide.obj", m_MeshList);
	D3DEngine::Mesh* GroundTileMesh = new D3DEngine::Mesh("./Models/GroundTile.obj", m_MeshList);
	D3DEngine::Mesh* GolfClubMesh = new D3DEngine::Mesh("./Models/GolfClub.obj", m_MeshList);

	D3DEngine::MeshResource* BackRes = m_MeshList->GetModel("./Models/CourseBack.obj");
	D3DEngine::MeshResource* SideRes = m_MeshList->GetModel("./Models/CourseSide.obj");

	//Back and Top
	physicsEngine->AddAABBFromMesh(BackRes->GetVertices(), BackRes->GetVERTEXSIZE(), BackRes->GetIndices(), BackRes->GetINDEXSIZE());
	physicsEngine->AddAABBFromMesh(BackRes->GetVertices(), BackRes->GetVERTEXSIZE(), BackRes->GetIndices(), BackRes->GetINDEXSIZE());
	//Sides
	for(int i = 0; i < 8; i++)
		physicsEngine->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());

	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(1).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 3.475), 0.0f, 0.0f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(2).SetPosition(D3DEngine::Vector3f(5.0f, 0.0f, 0.0f));
	//SideA
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(3).SetPosition(D3DEngine::Vector3f(4.1f, 0.0f, 1.089f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(4).SetPosition(D3DEngine::Vector3f(4.1f-2.089, 0.0f, 1.089f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(5).SetPosition(D3DEngine::Vector3f(4.1f - (2.089*2), 0.0f, 1.089f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(6).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 3), 0.0f, 1.089f));
	//SideB
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(7).SetPosition(D3DEngine::Vector3f(4.1f, 0.0f, -1.078f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(8).SetPosition(D3DEngine::Vector3f(4.1f - 2.089, 0.0f, -1.078f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(9).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 2), 0.0f, -1.078f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(10).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 3), 0.0f, -1.078f));

	D3DEngine::GameObject* GolfClubObject = new D3DEngine::GameObject();
	GolfClubObject->AddComponent(new D3DEngine::MeshRenderer(GolfClubMesh, MetalMat));
	GolfClubObject->GetTransform()->SetPosition(D3DEngine::Vector3f(-1.4, 0, 0));
	GolfClubObject->GetTransform()->SetScaling(D3DEngine::Vector3f(8, 8, 6));
	

	//Sphere
	D3DEngine::GameObject* Sphere = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* SphereMeshRenderer = new D3DEngine::MeshRenderer(BallMesh, GolfBallMat);
	Sphere->GetTransform()->SetScaling(D3DEngine::Vector3f(0.1f, 0.1f, 0.1f));
	Sphere->AddComponent(SphereMeshRenderer);
	Sphere->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(0), true));
	GolfClubObject->AddComponent(new GolfClub(Sphere, &m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(0), 8, 0.5, 10));
	Sphere->AddChild(GolfClubObject);
	//End Sphere





	D3DEngine::GameObject* FrontBarrier = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* PlaneMeshRenderer = new D3DEngine::MeshRenderer(BackMesh, SideMat);
	FrontBarrier->AddComponent(PlaneMeshRenderer);
	FrontBarrier->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(1)));

	D3DEngine::GameObject* BackBarrier = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* PlaneMeshRenderer2 = new D3DEngine::MeshRenderer(BackMesh, SideMat);
	BackBarrier->AddComponent(PlaneMeshRenderer2);
	BackBarrier->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(2)));

	D3DEngine::GameObject* GTile1 = new D3DEngine::GameObject();
	GTile1->AddComponent(new D3DEngine::MeshRenderer(GroundTileMesh, material));
	GTile1->GetTransform()->SetPosition(D3DEngine::Vector3f(3.9, -0.05, 0));

	D3DEngine::GameObject* GTile2 = new D3DEngine::GameObject();
	GTile2->AddComponent(new D3DEngine::MeshRenderer(GroundTileMesh, material));
	GTile2->GetTransform()->SetPosition(D3DEngine::Vector3f(3.9 - (2 * 1), -0.05, 0));

	D3DEngine::GameObject* GTile3 = new D3DEngine::GameObject();
	GTile3->AddComponent(new D3DEngine::MeshRenderer(GroundTileMesh, material));
	GTile3->GetTransform()->SetPosition(D3DEngine::Vector3f(3.9 - (2 * 2), -0.05, 0));

	D3DEngine::GameObject* GTile4 = new D3DEngine::GameObject();
	GTile4->AddComponent(new D3DEngine::MeshRenderer(GroundTileMesh, material));
	GTile4->GetTransform()->SetPosition(D3DEngine::Vector3f(3.9 - (2 * 3), -0.05, 0));

	//4.1f, 0.0f, 1.089f)
	//SideA
	D3DEngine::GameObject* Side1 = new D3DEngine::GameObject();
	Side1->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side1->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(3)));

	D3DEngine::GameObject* Side2 = new D3DEngine::GameObject();
	Side2->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side2->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(4)));

	D3DEngine::GameObject* Side3 = new D3DEngine::GameObject();
	Side3->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side3->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(5)));

	D3DEngine::GameObject* Side4 = new D3DEngine::GameObject();
	Side4->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side4->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(6)));
	//SideB
	D3DEngine::GameObject* Side5 = new D3DEngine::GameObject();
	Side5->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side5->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(7)));

	D3DEngine::GameObject* Side6 = new D3DEngine::GameObject();
	Side6->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side6->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(8)));

	D3DEngine::GameObject* Side7 = new D3DEngine::GameObject();
	Side7->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side7->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(9)));

	D3DEngine::GameObject* Side8 = new D3DEngine::GameObject();
	Side8->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side8->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(10)));


	
	

	//Lights
	D3DEngine::GameObject* DirectionalLightObject = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(1, 1, 1), 0.9f);
	DirectionalLightObject->AddComponent(directionalLight);
	DirectionalLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(-45.0f)));

	D3DEngine::GameObject* DirectionalLightObject2 = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight2 = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(1, 1, 1), 0.9f);
	DirectionalLightObject2->AddComponent(directionalLight2);
	DirectionalLightObject2->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(45.0f)));
	//Lights End
	
	D3DEngine::GameObject* PhysicsEngineObj = new D3DEngine::GameObject();
	PhysicsEngineObj->AddComponent(m_PhysicsEngineComponent);
	
	AddObject(CameraObject);
	AddObject(Sphere);
	AddObject(PhysicsEngineObj);
	AddObject(DirectionalLightObject);
	AddObject(DirectionalLightObject2);
	AddObject(FrontBarrier);
	AddObject(BackBarrier);
	//GTile
	AddObject(GTile1);
	AddObject(GTile2);
	AddObject(GTile3);
	AddObject(GTile4);
	//SideA
	AddObject(Side1);
	AddObject(Side2);
	AddObject(Side3);
	AddObject(Side4);
	//SideB
	AddObject(Side5);
	AddObject(Side6);
	AddObject(Side7);
	AddObject(Side8);
}

void MiniGolf::Input(D3DEngine::GetInput* input, float Delta)
{
	input->Update();

	m_RootObject->Input(input, Delta);
}