#include "Game.h"

Game::Game():
	m_pCurrentState(nullptr)
{
}

Game::~Game()
{
}

void Game::Run()
{
	if(m_pCurrentState == nullptr)
		return;

	//TODO: add timer to get correct delta time
	float delta = 0.13f;

	m_pCurrentState->Update(delta);
	m_pCurrentState->Render();
}

void Game::Initialize()
{
}

void Game::Shutdown()
{
}

void Game::Pause(bool bPause)
{
	if(m_pCurrentState != nullptr)
	{
		if(bPause)
		{
			m_pCurrentState->Pause();
		}
		else
		{
			m_pCurrentState->Unpause();
		}
	}
}