#include "Game.h"
#include "MSG_GoToState.h"
#include "GameplayState.h"

Game::Game():
	m_pCurrentState(nullptr), m_pMessageManager(nullptr)
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
	float delta = 1 / 60.0f;

	m_pCurrentState->Update(delta);
	m_pCurrentState->Render();

	if(m_pMessageManager == nullptr)
		return;
	
	m_pMessageManager->ProcessMessages();
}

void Game::Initialize()
{
	m_pMessageManager = CSGD_MessageSystem::GetInstance();
	m_pMessageManager->Initialize((IMessageReceiver*)this);

	//TODO: remove this test code
	ChangeState(new GameplayState());
}

void Game::Shutdown()
{
	if(m_pMessageManager != nullptr)
	{
		m_pMessageManager->Terminate();
		m_pMessageManager = nullptr;
	}
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

void Game::MessageProc(IMessage* pMessage)
{
	if(pMessage == nullptr)
		return;

	switch (pMessage->GetMessageID())
	{
	case MSG_GO_TO_MAIN_MENU_STATE:
		break;
	case MSG_GO_TO_OPTIONS_STATE:
		break;
	case MSG_GO_TO_CREDITS_STATE:
		break;
	case MSG_GO_TO_IN_GAME_MENU_STATE:
		break;
	case MSG_GO_TO_GAMEPLAY_STATE:
		ChangeState(new GameplayState());
		break;
	default:
		break;
	}
}

void Game::ChangeState(IGameState* newState)
{
	if(newState == nullptr)
		return;
	if(m_pCurrentState != nullptr)
		m_pCurrentState->Exit();
	delete m_pCurrentState;

	m_pCurrentState = newState;
	m_pCurrentState->Enter();
}