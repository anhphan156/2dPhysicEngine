#include "Force.h"
#include <math.h>

Vec2 Force::GenerateDragForce(Body& body, float strength){
	Vec2 dragForce = Vec2(0.f, 0.f);

	float bodyVelocityLengthSquare = body.velocity.MagnitudeSquared();

	if(bodyVelocityLengthSquare > 0.f){
		dragForce = body.velocity.UnitVector() * -1 * strength * bodyVelocityLengthSquare;
	}

	return dragForce;
}

Vec2 Force::GenerateSpringForce(const Body& body, const Vec2& anchor, float restLength, float k){
	Vec2 d = body.position - anchor;

	float displacement = d.Magnitude() - restLength; 

	Vec2 springForce = d.UnitVector() * -1 * k * displacement;

	return springForce;
}
