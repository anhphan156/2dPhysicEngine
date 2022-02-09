#include "Contact.h"

void Contact::ResolvePenetration(){
	if(a->IsStatic() && b->IsStatic()) return;

	const float depthovermass = depth / (a->invMass + b->invMass);
		
	const float da = depthovermass * a->invMass;
	const float db = depthovermass * b->invMass;

	//const float da = depth / (a->invMass + b->invMass) * a->invMass;
	//const float db = depth / (a->invMass + b->invMass) * b->invMass;

	a->position -= normal * da;
	b->position += normal * db;
}

void Contact::ResolveCollision(){
	ResolvePenetration();

	const Vec2 vrel = a->velocity - b->velocity;
	const float elasticity = std::min(a->restitution, b->restitution);

	const float impulseMagnitude = (vrel.Dot(normal) * -1 * (elasticity + 1)) / (a->invMass + b->invMass);

	const Vec2 impulseA = normal * impulseMagnitude;
	const Vec2 impulseB = normal * -impulseMagnitude;

	a->ApplyImpulse(impulseA);
	b->ApplyImpulse(impulseB);
}
