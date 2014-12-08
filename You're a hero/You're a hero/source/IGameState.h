#pragma once

class IGameState
{
public:
	IGameState();
	virtual ~IGameState() = 0;
	virtual void Enter(){};
	virtual void Leave(){};
	virtual void Update(float fDelta){};
	virtual void Render(){};
	virtual void Pause(){};
	virtual void Unpause(){};
};