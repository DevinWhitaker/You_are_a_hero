#pragma once

#include "IEntity.h"

class PlayerEntity
	: public IEntity
{
public:
	PlayerEntity(b2Body* pBody);
	virtual ~PlayerEntity();
	void Update(float fTimeStep);
	void Render();

private:
	//TODO: replace with animation
	int m_nImageId;
};