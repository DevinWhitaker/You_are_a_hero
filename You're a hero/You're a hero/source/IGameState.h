#pragma once
#include <Box2D/Box2D.h>
#include <string>
using namespace std;

class IGameState
{
public:
	IGameState(){};
	virtual ~IGameState(){};
	virtual void Enter(){};
	virtual void Exit(){};
	virtual void Update(float fDelta) = 0;
	virtual void Render(){};
	virtual void Pause(){};
	virtual void Unpause(){};
};