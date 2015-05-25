#include "PlayerEntity.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include <iostream>
using namespace std;

PlayerEntity::PlayerEntity(b2Body* pBody) :
	IEntity(pBody)
{
	m_nImageId = 0;
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::Update(float fTimeStep)
{
	if(CSGD_DirectInput::GetInstance()->KeyDown(DIK_RIGHTARROW))
	{
		b2Vec2 vec(30.0, 0.0);
		m_pPhysBody->ApplyForceToCenter(vec, true);
		cout << "right pressed.\n";
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_UPARROW))
	{
		b2Vec2 vec(0.0, -2500.0);
		m_pPhysBody->ApplyForceToCenter(vec, true);
		cout << "up pressed.";
	}
}

void PlayerEntity::Render()
{
	int x = m_pPhysBody->GetTransform().p.x;
	int y = m_pPhysBody->GetTransform().p.y;
	CSGD_TextureManager::GetInstance()->Draw(m_nImageId, x, y);
}