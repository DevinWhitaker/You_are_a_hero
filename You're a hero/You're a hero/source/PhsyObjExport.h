#pragma once
#include <Box2D/Box2D.h>
#include <list>
#include <utility>
#include <fstream>
using namespace std;

class PhsyObjExport
{
private:
	b2BodyDef m_b2BodyDef;
	list<pair<b2FixtureDef, b2Shape*>> m_lFixtures;

public:
	PhsyObjExport(const b2Body& body);
	~PhsyObjExport();
	void WriteOut(ofstream& fileStream);
};