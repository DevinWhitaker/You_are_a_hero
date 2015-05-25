#include "GameplayState.h"
#include "PhsyObjExport.h"
#include "PlayerEntity.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"

//TODO: implement a real player
PlayerEntity* g_Player = nullptr;

GameplayState::GameplayState():
	m_b2World(g_Gravity)
{
}

GameplayState:: ~GameplayState()
{
}

void GameplayState::Enter()
{
	OpenLoadingScreen();
	Load("nothing yet");// TODO: actually load a file
	CloseLoadingScreen();
	//TODO: delete
	CreateAndSavePhysicsObjects("TemplateFile");
	
	int id = CSGD_TextureManager::GetInstance()->LoadTexture(_T("SGD_DW_Hero.png"));
	//...this
}

void GameplayState::Exit()
{
}

void GameplayState::Update(float fDelta)
{
	m_b2World.Step(g_TimeStep, g_VelocityIterations, g_PositionIterations);
	CSGD_DirectInput::GetInstance()->ReadDevices();
	//delete
	g_Player->Update(fDelta);
}

void GameplayState::Render()
{
	//delete
	CSGD_Direct3D::GetInstance()->Clear( 0x000000 );

	CSGD_Direct3D::GetInstance()->DeviceBegin();
	CSGD_Direct3D::GetInstance()->SpriteBegin();

	g_Player->Render();

	CSGD_Direct3D::GetInstance()->SpriteEnd();
	CSGD_Direct3D::GetInstance()->DeviceEnd();

	CSGD_Direct3D::GetInstance()->Present();
}

void GameplayState::Pause()
{
}

void GameplayState::Unpause()
{
}

void GameplayState::Load(const string& )
{
}

void GameplayState::OpenLoadingScreen()
{
}

void GameplayState::CloseLoadingScreen()
{
}

void GameplayState::CreateAndSavePhysicsObjects(const string& fileName)
{
	//create rigid body
	b2BodyDef RigidBodyDef;
	RigidBodyDef.position.Set(0.0f, 400.0f);
	b2Body* pRigidBody = m_b2World.CreateBody(&RigidBodyDef);
	b2PolygonShape RigidBox;
	RigidBox.SetAsBox(50.0f, 10.0f);
	pRigidBody->CreateFixture(&RigidBox, 0.0f);
	PhsyObjExport RigidBodyExport(*pRigidBody);

	//create a dynamic body
	b2BodyDef DynamicBodyDef;
	DynamicBodyDef.type = b2_dynamicBody;
	DynamicBodyDef.position.Set(0.0f, 4.0f);
	b2Body* DynamicBody = m_b2World.CreateBody(&DynamicBodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	DynamicBody->CreateFixture(&fixtureDef);
	PhsyObjExport DynamicBodyExport(*DynamicBody);
	g_Player = new PlayerEntity(DynamicBody);

	//create a chain shape
	b2BodyDef ChainBodyDef;
	ChainBodyDef.position.Set(0.0f, 0.0f);
	b2Body* pChainBody = m_b2World.CreateBody(&ChainBodyDef);
	b2Vec2 vs[4];
	vs[0].Set(1.7f, 300.0f);
	vs[1].Set(200.0f, 300.25f);
	vs[2].Set(450.0f, 300.0f);
	vs[3].Set(-751.7f, 300.4f);
	b2ChainShape ChainShape;
	ChainShape.CreateChain(vs, 4);
	pChainBody->CreateFixture(&ChainShape, 0.0f);
	PhsyObjExport ChainBodyExport(*pChainBody);

	//write out the data
	/*ofstream LevelTemplate(fileName.c_str(), ios_base::binary);
	if(LevelTemplate.is_open())
	{
		RigidBodyExport.WriteOut(LevelTemplate);
		DynamicBodyExport.WriteOut(LevelTemplate);
		ChainBodyExport.WriteOut(LevelTemplate);
	}*/
	
}