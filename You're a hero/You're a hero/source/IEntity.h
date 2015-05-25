#pragma once

#include <Box2D\Box2D.h>

class IEntity
{
public:
	IEntity(b2Body* pBody = nullptr){
		m_pPhysBody = pBody;
		if(m_pPhysBody != nullptr)
			m_pPhysBody->SetUserData(this);
	}
	virtual ~IEntity(){};
	virtual void Update(float fTimeStep) = 0;
	virtual void Render() = 0;

protected:
	b2Body* m_pPhysBody;
};