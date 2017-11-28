#include "Level.h"

Level::Level(int LevelData[5][5],
	D3DEngine::Window* Window, D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine,
	D3DEngine::GameObject* RootObject)
{
	float RealLevelData[5][5] = {
		{ 1.9,	1.8,	2,	1.8,	1.9 } ,  //Row 0
		{ 1.8,	1.4,	1,	1.4,	1.8 } ,  //Row 1
		{ -2,	-1,		0,	1,		2 } ,	//Row 2
		{ -1.8,	-1.4,	-1,	-1.4,	-1.8 } ,  //Row 3
		{ -1.9,	-1.8,	-2,	-1.8,	-1.9 }    //Row 4
	};


	D3DEngine::PhysicsEngineComponent* m_PhysicsEngineComponent = new D3DEngine::PhysicsEngineComponent(physicsEngine);
	D3DEngine::GameObject* PhysicsEngineObj = new D3DEngine::GameObject();
	PhysicsEngineObj->AddComponent(m_PhysicsEngineComponent);
	RootObject->AddChild(PhysicsEngineObj);

	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	float Aspect = Window->GetWidth() / Window->GetHeight();
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

	int ObjectCount = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cerr << j << std::endl;
			if (LevelData[i][j] == 2)
			{
				m_PhysicsEngineComponent->GetPhysicsEngine()->AddObject(D3DEngine::PhysicsObject(new D3DEngine::BoundingSphere(D3DEngine::Vector3f(i*2, 0.0f, j*2), .2f), D3DEngine::Vector3f(0.0f, 0.0f, 0.0f)));
				ObjectCount++;
				int Num = ObjectCount - 1;

				//GolfClub
				D3DEngine::GameObject* GolfClubObject = new D3DEngine::GameObject();
				GolfClubObject->AddComponent(new D3DEngine::MeshRenderer(GolfClubMesh, MetalMat));
				GolfClubObject->GetTransform()->SetPosition(D3DEngine::Vector3f(-1.4, 0, 0));
				GolfClubObject->GetTransform()->SetScaling(D3DEngine::Vector3f(8, 8, 6));
				//End GolfClub
				//Sphere
				m_GameObjects.push_back(new D3DEngine::GameObject());
				m_GameObjects.back()->GetTransform()->SetScaling(D3DEngine::Vector3f(0.1f, 0.1f, 0.1f));
				m_GameObjects.back()->AddComponent(new D3DEngine::MeshRenderer(BallMesh, GolfBallMat));
				m_GameObjects.back()->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(Num), true));
				GolfClubObject->AddComponent(new GolfClub(m_GameObjects.back(), &m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(Num), 8, 0.5, 10));
				m_GameObjects.back()->AddChild(GolfClubObject);
				//End Sphere
			}
			if ((LevelData[i][j] == 1) || (LevelData[i][j] == 2))
			{
				D3DEngine::Vector3f TileCenter = D3DEngine::Vector3f(i * 2, -0.05, j * 2);
				D3DEngine::GameObject* Tile = new D3DEngine::GameObject();
				Tile->AddComponent(new D3DEngine::MeshRenderer(GroundTileMesh, material));
				Tile->GetTransform()->SetPosition(TileCenter);
				RootObject->AddChild(Tile);
				//I is Vertical
				//J is Horizontal
				if (j - 1 >= 0)
				{
					if (LevelData[i][j - 1] == 0)
					{
						//std::cerr << "Side Edge" << std::endl;
						//m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());
						//ObjectCount++;
						//int Num = ObjectCount - 1;
						////first
						////m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(Num).SetPosition(D3DEngine::Vector3f(i * -2, 0.0f, j * 1.5));
						//D3DEngine::Vector3f MyCenter = TileCenter;
						////MyCenter.SetZ(MyCenter.GetZ()*1.26);
						//m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(Num).SetPosition(MyCenter);

						//m_GameObjects.push_back(new D3DEngine::GameObject());
						//m_GameObjects.back()->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
						//m_GameObjects.back()->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(Num)));
						////RootObject->AddChild(m_GameObjects.back());
					}
				}
				if (j + 1 < 5)
				{
					if (LevelData[i][j + 1] == 0)
					{
						//std::cerr << "Side Edge" << std::endl;
						//m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());
						//ObjectCount++;
						//int Num = ObjectCount - 1;
						////first
						////m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(Num).SetPosition(D3DEngine::Vector3f(i * -2, 0.0f, j * 2.5));


						//D3DEngine::Vector3f MyCenter = TileCenter;
						////MyCenter.SetZ(MyCenter.GetZ()*0.74);
						//m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(Num).SetPosition(MyCenter);

						//m_GameObjects.push_back(new D3DEngine::GameObject());
						//m_GameObjects.back()->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
						//m_GameObjects.back()->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(Num)));
						////RootObject->AddChild(m_GameObjects.back());
					}
				}
			}
		}
	}
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



	RootObject->AddChild(DirectionalLightObject);
	RootObject->AddChild(DirectionalLightObject2);
	RootObject->AddChild(CameraObject);

	for (int i = 0; i < m_GameObjects.size(); i++)
		RootObject->AddChild(m_GameObjects.at(i));
}

Level::Level(
	D3DEngine::Window* Window, D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine,
	D3DEngine::GameObject* RootObject)
{

	D3DEngine::PhysicsEngineComponent* m_PhysicsEngineComponent = new D3DEngine::PhysicsEngineComponent(physicsEngine);
	D3DEngine::GameObject* PhysicsEngineObj = new D3DEngine::GameObject();
	PhysicsEngineObj->AddComponent(m_PhysicsEngineComponent);
	RootObject->AddChild(PhysicsEngineObj);

	physicsEngine->AddObject(D3DEngine::PhysicsObject(new D3DEngine::BoundingSphere(D3DEngine::Vector3f(0.0f, 0.0f, 0.0f), .2f), D3DEngine::Vector3f(0.0f, 0.0f, 0.0f)));

	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	float Aspect = Window->GetWidth() / Window->GetHeight();
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
	for (int i = 0; i < 8; i++)
		physicsEngine->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());

	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(1).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 3.475), 0.0f, 0.0f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(2).SetPosition(D3DEngine::Vector3f(5.0f, 0.0f, 0.0f));
	//SideA
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(3).SetPosition(D3DEngine::Vector3f(4.1f, 0.0f, 1.089f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(4).SetPosition(D3DEngine::Vector3f(4.1f - 2.089, 0.0f, 1.089f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(5).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 2), 0.0f, 1.089f));
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

	
	RootObject->AddChild(CameraObject);
	RootObject->AddChild(Sphere);
	
	RootObject->AddChild(DirectionalLightObject);
	RootObject->AddChild(DirectionalLightObject2);
	RootObject->AddChild(FrontBarrier);
	RootObject->AddChild(BackBarrier);
	//GTile
	RootObject->AddChild(GTile1);
	RootObject->AddChild(GTile2);
	RootObject->AddChild(GTile3);
	RootObject->AddChild(GTile4);
	//SideA
	RootObject->AddChild(Side1);
	RootObject->AddChild(Side2);
	RootObject->AddChild(Side3);
	RootObject->AddChild(Side4);
	//SideB
	RootObject->AddChild(Side5);
	RootObject->AddChild(Side6);
	RootObject->AddChild(Side7);
	RootObject->AddChild(Side8);


}


Level::~Level()
{
}
