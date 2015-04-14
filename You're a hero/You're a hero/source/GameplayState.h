#pragma once
#include "IGameState.h"

//Simulation constants
const b2Vec2 g_Gravity(0.0f, -10.0f);
const float32 g_TimeStep = 1.0f / 60.0f;
const int32 g_VelocityIterations = 8;
const int32 g_PositionIterations = 3;

class GameplayState : public IGameState
{
private:
	b2World m_b2World;

	void Load(const string& );
	void OpenLoadingScreen();
	void CloseLoadingScreen();

public:
	GameplayState();
	virtual ~GameplayState();
	void Enter();
	void Exit();
	void Update(float fDelta);
	void Render();
	void Pause();
	void Unpause();
};