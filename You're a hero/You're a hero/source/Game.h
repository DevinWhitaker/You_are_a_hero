#pragma once

#include "IGameState.h"

class Game
{
public:
	Game();
	~Game();
	void Run();
	void Shutdown();
	void Pause(bool bPause);
	void Initialize();

private:
	IGameState*	m_pCurrentState;
};