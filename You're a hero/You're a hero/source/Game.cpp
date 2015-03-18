#include "Game.h"
#include "MSG_GoToState.h"

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
	float delta = 0.13f;

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
		break;
	default:
		break;
	}
}