//Includes
#include "Level.h"

void Level::TranslateHelper(float x, float z, int CurCount, D3DEngine::Vector3f tileCenter,
	D3DEngine::PhysicsEngineComponent* PhysicsEngineComponent)
{
	//Get the tile center
	D3DEngine::Vector3f MyCenter = tileCenter;
	//Update the center to the object position
	MyCenter.SetX(MyCenter.GetX() - x);
	MyCenter.SetZ(MyCenter.GetZ() - z);
	MyCenter.SetY(0.1f);
	//Update the physics objects position
	PhysicsEngineComponent->GetPhysicsEngine()->GetObject(CurCount)->SetPosition(MyCenter);
}

void Level::CreateHelper(int CurCount,
	D3DEngine::Mesh* mesh, D3DEngine::Material* material,
	D3DEngine::PhysicsEngineComponent* PhysicsEngineComponent, D3DEngine::GameObject* RootObject)
{
	//Create new game object
	D3DEngine::GameObject* NewObject = new D3DEngine::GameObject();
	//Add a mesh renderer component to the object
	NewObject->AddComponent(new D3DEngine::MeshRenderer(mesh, material));
	//Add a physics object component to the object
	NewObject->AddComponent(new D3DEngine::PhysicsObjectComponent(PhysicsEngineComponent->GetPhysicsEngine()->GetObject(CurCount)));
	//Add the object to the scene
	RootObject->AddChild(NewObject);
}

Level::Level(int NumOfPlayers, int LevelData[7][7],
	D3DEngine::Window* Window, D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine,
	D3DEngine::GameObject* RootObject)
{
	//Setup the physics engine component
	m_PhysicsEngineComponent = new D3DEngine::PhysicsEngineComponent(physicsEngine);
	D3DEngine::GameObject* PhysicsEngineObj = new D3DEngine::GameObject();
	PhysicsEngineObj->AddComponent(m_PhysicsEngineComponent);
	RootObject->AddChild(PhysicsEngineObj);	//Add the physics object to the scene

	//Create the camera object
	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	float Aspect = Window->GetWidth() / Window->GetHeight();
	CameraObject->AddComponent(new D3DEngine::Camera(TO_RADIANS(90.0f), Aspect, 0.01f, 1000.0f));
	CameraObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 0, 0), TO_RADIANS(30.0f))); //Tilt Down
	CameraObject->GetTransform()->SetPosition(D3DEngine::Vector3f(-8.0f, 22.0f, 0.0f));
	CameraObject->AddComponent(new D3DEngine::FreeLook());

	//Materials, Create and load each material needed
	D3DEngine::Material* GroundTexture = new D3DEngine::Material();						
	GroundTexture->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/GolfTexture.png"));
	GroundTexture->AddFloat("SpecularIntensity", 0.01);
	GroundTexture->AddFloat("SpecularExponent", 42);
	m_MaterialList.push_back(GroundTexture);

	D3DEngine::Material* GolfBallMat = new D3DEngine::Material();
	GolfBallMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/GolfBallTexture.png"));
	GolfBallMat->AddFloat("SpecularIntensity", 1);
	GolfBallMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(GolfBallMat);

	D3DEngine::Material* SideMat = new D3DEngine::Material();
	SideMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Wood.png"));
	SideMat->AddFloat("SpecularIntensity", 1);
	SideMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(SideMat);

	D3DEngine::Material* MetalMat = new D3DEngine::Material();
	MetalMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Metal.png"));
	MetalMat->AddFloat("SpecularIntensity", 1);
	MetalMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(MetalMat);

	D3DEngine::Material* FlagMat = new D3DEngine::Material();
	FlagMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/FlagTexture.png"));
	FlagMat->AddFloat("SpecularIntensity", 1);
	FlagMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(FlagMat);

	D3DEngine::Material* StartZoneMat = new D3DEngine::Material();
	StartZoneMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/GolfStrtZone.png"));
	StartZoneMat->AddFloat("SpecularIntensity", 1);
	StartZoneMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(StartZoneMat);
	//End Materials

	//Load Meshes
	D3DEngine::Mesh BackMesh = D3DEngine::Mesh("./Models/CourseBack.obj", &m_MeshList);
	D3DEngine::Mesh SideMesh = D3DEngine::Mesh("./Models/CourseSide.obj", &m_MeshList);
	//Get Mesh Resources for Physics Objects
	D3DEngine::MeshResource* BackRes = m_MeshList.GetModel("./Models/CourseBack.obj");
	D3DEngine::MeshResource* SideRes = m_MeshList.GetModel("./Models/CourseSide.obj");

	//Set offset value of 1, as the level data as 1 layer of padding
	int PaddOffset = 1;

	//Init object count to 0
	int ObjectCount = 0;

	//Find the Special objects And make sure it is created first. (Ball and Flag
	for (int i = PaddOffset; i < 5 + PaddOffset; i++)
	{
		for (int j = PaddOffset; j < 5 + PaddOffset; j++)
		{
			if (LevelData[i][j] == 2) //Ball
			{
				//Get the center of the current tiles
				D3DEngine::Vector3f TileCenter = D3DEngine::Vector3f(i * 2, -0.05, j * 2);
				//Create new object for the starting tile zone
				D3DEngine::GameObject* TileStrt = new D3DEngine::GameObject();
				TileStrt->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/GolfBallStart.obj", &m_MeshList), StartZoneMat));
				TileStrt->GetTransform()->Rotate(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(90));
				//Update the position of the tile starting zone
				D3DEngine::Vector3f MyPos = TileCenter;
				MyPos.SetY(-0.07f);
				TileStrt->GetTransform()->SetPosition(MyPos);
				//Set the scale of the tile starting zone
				TileStrt->GetTransform()->SetScaling(D3DEngine::Vector3f(0.5,1,0.5));
				RootObject->AddChild(TileStrt);	//Add the tile starting zone to the scene
				//Add a Bounding Sphere object to the physics engine
				m_PhysicsEngineComponent->GetPhysicsEngine()->AddObject(new D3DEngine::PhysicsObject(new D3DEngine::BoundingSphere(D3DEngine::Vector3f(i * 2, -0.5f, j * 2), .1f), D3DEngine::Vector3f(0.0f, 0.0f, 0.0f)));

				//Display Message
				std::cerr << "Ball Proccessing" << std::endl;
				//GolfClub
				D3DEngine::GameObject* GolfClubObject = new D3DEngine::GameObject();
				GolfClubObject->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/GolfClub.obj", &m_MeshList), MetalMat));
				GolfClubObject->GetTransform()->SetPosition(D3DEngine::Vector3f(-1.4, 0, 0));
				GolfClubObject->GetTransform()->SetScaling(D3DEngine::Vector3f(8, 8, 6));
				//End GolfClub

				//Sphere
				D3DEngine::GameObject* GolfBall = new D3DEngine::GameObject();
				GolfBall->GetTransform()->SetScaling(D3DEngine::Vector3f(0.1f, 0.1f, 0.1f));

				D3DEngine::Vector3f MyCenter = TileCenter;
				MyCenter.SetY(0.1f);

				//Update Camera Position
				D3DEngine::Vector3f CameraPos = MyCenter;
				CameraPos.SetX(CameraPos.GetX() + 0);
				CameraPos.SetY(CameraPos.GetY() + 2);
				CameraPos.SetZ(CameraPos.GetZ() - 1);
				CameraObject->GetTransform()->SetPosition(CameraPos); //Update Camera to Ball
																	  //End Update Camera Position
																	  //Update position
				m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectCount)->SetPosition(MyCenter);
				GolfBall->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/Ball.obj", &m_MeshList), GolfBallMat));
				GolfBall->AddComponent(new D3DEngine::PhysicsObjectComponent(m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectCount), true));

				GolfClubObject->AddComponent(new GolfClub(GolfBall, m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectCount), 8, 0.5, 10));
				GolfBall->AddChild(GolfClubObject);
				RootObject->AddChild(GolfBall);	//Add golf ball to the scene
				//End Sphere

				//Create Players
				m_Players = std::vector<Player*>();
				for (int i = 0; i < NumOfPlayers; i++)
				{
					//Create new player
					Player* m_Player = new Player(renderEngine, GolfBall, m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectCount), i + 1);
					m_Player->SetBallStartPos(m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectCount)->GetPosition());
					//Add player to the players list
					m_Players.push_back(m_Player);
				}
				//Set ALL players Score to 0
				for (int i = NumOfPlayers - 1; i > -1; i--)
					m_Players[i]->IncreaseScore();

				ObjectCount++;	//Increment the object count
			}
			if (LevelData[i][j] == 3) //Flag
			{
				//Get the center of the current tiles
				D3DEngine::Vector3f TileCenter = D3DEngine::Vector3f(i * 2, 0.0, j * 2);

				//Add Pocket
				m_Pocket = new Pocket(TileCenter, 0.2f);

				//Add Hole
				D3DEngine::GameObject* Hole = new D3DEngine::GameObject();
				Hole->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/Hole.obj", &m_MeshList), StartZoneMat));
				//Update hole position
				D3DEngine::Vector3f MyPos = TileCenter;
				MyPos.SetY(-0.02f);
				Hole->GetTransform()->SetPosition(MyPos);
				Hole->GetTransform()->SetScaling(D3DEngine::Vector3f(0.1f, 0.0f, 0.1f));
				RootObject->AddChild(Hole);	//Add hole to scene
				//End Add Hole

				//Add Flag
				D3DEngine::GameObject* FlagBack = new D3DEngine::GameObject();
				FlagBack->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/Flag.obj", &m_MeshList), FlagMat));
				FlagBack->GetTransform()->SetPosition(D3DEngine::Vector3f(0.8f, 2.35f, 0.0f));
				FlagBack->GetTransform()->SetScaling(D3DEngine::Vector3f(1.0f, 0.3f, 1.0f));
				FlagBack->GetTransform()->Rotate(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(270));

				D3DEngine::GameObject* FlagFront = new D3DEngine::GameObject();
				FlagFront->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/Flag.obj", &m_MeshList), FlagMat));
				FlagFront->GetTransform()->SetPosition(D3DEngine::Vector3f(0.8f, 2.5f, 0.0f));
				FlagFront->GetTransform()->SetScaling(D3DEngine::Vector3f(1.0f, 0.3f, 1.0f));
				FlagFront->GetTransform()->SetRotation(0, 1, 0, 0);
				FlagFront->GetTransform()->Rotate(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(270));
				FlagFront->GetTransform()->Rotate(D3DEngine::Vector3f(0, 0, 1), TO_RADIANS(180));
				//End Add Flag

				//Add Flag Shaft
				D3DEngine::GameObject* FlagShaft = new D3DEngine::GameObject();
				FlagShaft->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/FlagShaft.obj", &m_MeshList), MetalMat));
				FlagShaft->GetTransform()->SetPosition(TileCenter);
				FlagShaft->GetTransform()->SetScaling(D3DEngine::Vector3f(0.2f, 1.0f, 0.2f));;

				FlagShaft->AddChild(FlagBack);	//Add flag back as a child to flag shaft
				FlagShaft->AddChild(FlagFront);	//Add flag front as a child to flag shaft

				RootObject->AddChild(FlagShaft);	//Add flag to the scene
				//End Add Flag Shaft
			}
		}
	}

	//Create remaing physics objects
	for (int i = PaddOffset; i < 5 + PaddOffset; i++)
	{
		for (int j = PaddOffset; j < 5 + PaddOffset; j++)
		{
			//Check if the current data position isnt empty
			if ((LevelData[i][j] == 1) || (LevelData[i][j] == 2) || (LevelData[i][j] == 3))
			{
				//Get the tile center
				D3DEngine::Vector3f TileCenter = D3DEngine::Vector3f(floor(i * 2), -0.05, floor(j * 2));
				//Create a tile object (the ground tile)
				D3DEngine::GameObject* Tile = new D3DEngine::GameObject();
				Tile->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/GroundTile.obj", &m_MeshList), GroundTexture));
				Tile->GetTransform()->SetPosition(TileCenter);
				RootObject->AddChild(Tile);	//Add the ground tile to the scene

				//Checks if there is free space adjacent to the current tile, if there is then a wall needs to be created on the correct side
				if (j - 1 >= 0)
				{
					if (LevelData[i][j - 1] <= 0)
					{
						//Wall needs to be created on the left side of the tile
						LevelData[i][j - 1] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());

						//Display message
						std::cerr << "Wall Back Proccessing: Moved Left" << std::endl;
						//Update the objects position, then create it
						TranslateHelper(0.0f, 1.08f, ObjectCount, TileCenter, m_PhysicsEngineComponent);
						CreateHelper(ObjectCount, new D3DEngine::Mesh("./Models/CourseSide.obj", &m_MeshList), SideMat, m_PhysicsEngineComponent, RootObject);

						ObjectCount++;	//Increment object count
					}
				}
				if (j + 1 < 7)
				{
					if (LevelData[i][j + 1] <= 0)
					{
						//Wall needs to be created on the right side of the tile
						LevelData[i][j + 1] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());

						//Display message
						std::cerr << "Wall Back Proccessing: Moved Right" << std::endl;
						//Update the objects position, then create it
						TranslateHelper(0.0f, -1.08f, ObjectCount, TileCenter, m_PhysicsEngineComponent);
						CreateHelper(ObjectCount, new D3DEngine::Mesh("./Models/CourseSide.obj", &m_MeshList), SideMat, m_PhysicsEngineComponent, RootObject);

						ObjectCount++;	//Increment object count
					}
				}
				if (i - 1 >= 0)
				{
					if (LevelData[i - 1][j] <= 0)
					{
						//Wall needs to be created on the top side of the tile
						LevelData[i - 1][j] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(BackRes->GetVertices(), SideRes->GetVERTEXSIZE(), BackRes->GetIndices(), BackRes->GetINDEXSIZE());

						//Display message
						std::cerr << "Wall Back Proccessing: Moved Up" << std::endl;
						//Update the objects position, then create it
						TranslateHelper(1.11f, 0.0f, ObjectCount, TileCenter, m_PhysicsEngineComponent);
						CreateHelper(ObjectCount, new D3DEngine::Mesh("./Models/CourseBack.obj", &m_MeshList), SideMat, m_PhysicsEngineComponent, RootObject);

						ObjectCount++;	//Increment object count
					}
				}
				if (i + 1 < 7)
				{
					if (LevelData[i + 1][j] <= 0)
					{
						//Wall needs to be created on the bottom side of the tile
						LevelData[i + 1][j] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(BackRes->GetVertices(), BackRes->GetVERTEXSIZE(), BackRes->GetIndices(), BackRes->GetINDEXSIZE());

						//Display message
						std::cerr << "Wall Back Proccessing: Moved Down" << std::endl;
						//Update the objects position, then create it
						TranslateHelper(-1.12f, 0.0f, ObjectCount, TileCenter, m_PhysicsEngineComponent);
						CreateHelper(ObjectCount, new D3DEngine::Mesh("./Models/CourseBack.obj", &m_MeshList), SideMat, m_PhysicsEngineComponent, RootObject);

						ObjectCount++;	//Increment object count
					}
				}
			}
		}
	}

	//Create a directional light for the level
	D3DEngine::GameObject* DirectionalLightObject = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(0.5, 0.5, 0.5), 0.1f);
	DirectionalLightObject->AddComponent(directionalLight);
	DirectionalLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(-45.0f)));

	RootObject->AddChild(CameraObject);				//Add the camera to the scene
	RootObject->AddChild(DirectionalLightObject);	//Add the directional light to the scene
}

Level::~Level()
{
	//Display Message
	std::cerr << "Destructor: Level" << std::endl;
}

void Level::Destroy()
{
	//Delete all the materials
	for (int i = 0; i < m_MaterialList.size(); i++)
		delete m_MaterialList[i];
	m_MaterialList.clear();
	//Delete all the players
	for (int i = 0; i < m_Players.size(); i++)
		delete m_Players[i];
	m_Players.clear();
	//Delete the pocket
	delete m_Pocket;
}

void Level::ResetBall()
{
	//Set the current ball to being active
	m_Players[m_CurrentPlayer]->Active();
}

bool Level::Update(float Delta)
{
	//Check if the current player has finished
	if (!m_Finished)
	{
		//Check if the pocket is colliding with the ball
		if (m_Pocket->IsColliding(m_Players[m_CurrentPlayer]->GetBall()))
		{
			//Add Point for current player, as the ball went into the hole
			m_Players[m_CurrentPlayer]->IncreaseScore();
			//Check if there is another player
			if (m_CurrentPlayer < m_Players.size() - 1)
			{
				//Move to next player
				m_CurrentPlayer++;
				//Set Next Player to Being Active
				m_Players[m_CurrentPlayer]->Active();
			}
			else
			{
				//Display message
				std::cerr << "No More Players" << std::endl;
				//Set to low velocity
				m_Players[m_CurrentPlayer]->GetBall()->SetVelocity(D3DEngine::Vector3f(0.1f, 0.00f, 0.1f));
				//Set m_Finished to true
				m_Finished = true;
				//Return true (all players have finished the hole)
				return true;
			}
		}
		//Update the current player
		m_Players[m_CurrentPlayer]->Update(Delta);
	}
	//return false (not all players have finished the hole)
	return false;
}