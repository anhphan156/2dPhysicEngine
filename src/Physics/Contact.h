#ifndef CONTACT_H
#define CONTACT_H

#include "Body.h"
#include "Vec2.h"
#include <memory>

struct Contact{
	std::shared_ptr<Body> a;	
	std::shared_ptr<Body> b;	

	Vec2 normal;

	Vec2 start;
	Vec2 end;

	float depth;

	void ResolvePenetration();
	void ResolveCollision();
};

#endif
