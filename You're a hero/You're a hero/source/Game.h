#pragma once

#include "IGameState.h"
#include "../SGD Wrappers/CSGD_MessageSystem.h"

class Game : public IMessageReceiver
{
public:
	Game();
	virtual ~Game();
	void Run();
	void Shutdown();
	void Pause(bool bPause);
	void Initialize();
	virtual void MessageProc(IMessage*);

private:
	IGameState*	m_pCurrentState;
	CSGD_MessageSystem* m_pMessageManager;
};