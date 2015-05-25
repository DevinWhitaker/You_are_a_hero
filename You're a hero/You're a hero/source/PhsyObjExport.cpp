#include "PhsyObjExport.h"

PhsyObjExport::PhsyObjExport(const b2Body& body)
{
	//save body definition
	m_b2BodyDef.userData = NULL;
	m_b2BodyDef.position = body.GetPosition();
	m_b2BodyDef.angle = body.GetAngle();
	m_b2BodyDef.linearVelocity = body.GetLinearVelocity();
	m_b2BodyDef.angularVelocity = body.GetAngularVelocity();
	m_b2BodyDef.linearDamping = body.GetLinearDamping();
	m_b2BodyDef.angularDamping = body.GetAngularDamping();
	m_b2BodyDef.allowSleep = body.IsSleepingAllowed();
	m_b2BodyDef.awake = body.IsAwake();
	m_b2BodyDef.fixedRotation = body.IsFixedRotation();
	m_b2BodyDef.bullet = body.IsBullet();
	m_b2BodyDef.type = body.GetType();
	m_b2BodyDef.active = body.IsActive();
	m_b2BodyDef.gravityScale = body.GetGravityScale();

	//save fixtures
	for (const b2Fixture* f = body.GetFixtureList(); f; f = f->GetNext())
	{
		b2FixtureDef fixtureDef;
		fixtureDef.shape = NULL;
		fixtureDef.userData = NULL;
		fixtureDef.friction = f->GetFriction();
		fixtureDef.restitution = f->GetRestitution();
		fixtureDef.density = f->GetDensity();
		fixtureDef.isSensor = f->IsSensor();

		b2Shape* shapeDef = nullptr;

		switch (f->GetType())
		{
		case b2Shape::Type::e_circle:
		{
			b2CircleShape* circleDef = new b2CircleShape;
			circleDef->m_radius = f->GetShape()->m_radius;
			circleDef->m_p = ((b2CircleShape*)f->GetShape())->m_p;
			shapeDef = circleDef;
		}
		break;
		case b2Shape::Type::e_edge:
		{
			b2EdgeShape* edgeDef = new b2EdgeShape;
			edgeDef->m_radius = f->GetShape()->m_radius;
			edgeDef->Set( ((b2EdgeShape*)f->GetShape())->m_vertex1, ((b2EdgeShape*)f->GetShape())->m_vertex2 );
			edgeDef->m_vertex0 = ((b2EdgeShape*)f->GetShape())->m_vertex0;
			edgeDef->m_vertex3 = ((b2EdgeShape*)f->GetShape())->m_vertex3;
			edgeDef->m_hasVertex0 = ((b2EdgeShape*)f->GetShape())->m_hasVertex0;
			edgeDef->m_hasVertex3 = ((b2EdgeShape*)f->GetShape())->m_hasVertex3;
			shapeDef = edgeDef;
		}
		break;
		case b2Shape::Type::e_polygon:
		{
			b2PolygonShape* polyDef = new b2PolygonShape;
			polyDef->m_radius = f->GetShape()->m_radius;
			polyDef->Set( ((b2PolygonShape*)f->GetShape())->m_vertices, ((b2PolygonShape*)f->GetShape())->m_count );
			shapeDef = polyDef;
		}
		break;
		case b2Shape::Type::e_chain:
		{
			b2ChainShape* chainDef = new b2ChainShape;
			chainDef->m_radius = f->GetShape()->m_radius;
			chainDef->CreateChain( ((b2ChainShape*)f->GetShape())->m_vertices, ((b2ChainShape*)f->GetShape())->m_count );
			chainDef->SetPrevVertex( ((b2ChainShape*)f->GetShape())->m_prevVertex );
			chainDef->SetNextVertex( ((b2ChainShape*)f->GetShape())->m_nextVertex );
			chainDef->m_hasPrevVertex = ((b2ChainShape*)f->GetShape())->m_hasPrevVertex;
			chainDef->m_hasNextVertex = ((b2ChainShape*)f->GetShape())->m_hasNextVertex;
			shapeDef = chainDef;
		}
		break;
		default:
			break;
		}

		m_lFixtures.push_back( make_pair(fixtureDef, shapeDef) );
	}
}

PhsyObjExport::~PhsyObjExport()
{
	list<pair<b2FixtureDef, b2Shape*>>::iterator iter = m_lFixtures.begin();
	for(; iter != m_lFixtures.end(); ++iter)
	{
		delete iter->second;
	}
}

void PhsyObjExport::WriteOut(ofstream& fileStream)
{
	//make sure the file is open in binary and has no errors
	if(!fileStream.is_open() || !fileStream.good() ||
		!(fileStream._Openmask & ios_base::binary) )
		return;

	fileStream.write((char*)&m_b2BodyDef, sizeof(b2BodyDef));
	
	size_t fixtureCount = m_lFixtures.size();
	fileStream.write((char*)&fixtureCount, sizeof(size_t));

	list<pair<b2FixtureDef, b2Shape*>>::iterator iter = m_lFixtures.begin();
	for(; iter != m_lFixtures.end(); ++iter)
	{
		fileStream.write((char*)&(iter->first), sizeof(b2FixtureDef));
		b2Shape::Type shapeType = iter->second->GetType();
		fileStream.write((char*)&(shapeType), sizeof(b2Shape::Type));

		switch (shapeType)
		{
		case b2Shape::Type::e_circle:
		{
			fileStream.write((char*)iter->second, sizeof(b2CircleShape));
		}
		break;
		case b2Shape::Type::e_edge:
		{
			fileStream.write((char*)iter->second, sizeof(b2EdgeShape));
		}
		break;
		case b2Shape::Type::e_polygon:
		{
			fileStream.write((char*)iter->second, sizeof(b2PolygonShape));
		}
		break;
		case b2Shape::Type::e_chain:
		{
			fileStream.write((char*)iter->second, sizeof(b2ChainShape));
		}
		break;
		default:
			break;
		}
	}
}