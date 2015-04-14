#include "GameplayState.h"

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
	Load("nothing yet");
	CloseLoadingScreen();
}

void GameplayState::Exit()
{
}

void GameplayState::Update(float fDelta)
{
	m_b2World.Step(g_TimeStep, g_VelocityIterations, g_PositionIterations);
}

void GameplayState::Render()
{
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