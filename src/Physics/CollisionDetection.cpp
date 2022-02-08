#include <math.h>
#include <memory>
#include "CollisionDetection.h"
#include "Body.h"
#include "Contact.h"
#include "Vec2.h"

bool CollisionDetection::CollisionDetection(std::shared_ptr<Body> a, std::shared_ptr<Body> b, Contact& contact){
	if(a->shape->GetShape() == CIRCLE && b->shape->GetShape() == CIRCLE){
		return CollisionDetectionCircleCircle(a, b, contact);			
	}

	return true;
}
bool CollisionDetection::CollisionDetectionCircleCircle(std::shared_ptr<Body> a, std::shared_ptr<Body> b, Contact& contact){
	const auto aCircle = std::static_pointer_cast<Circle>(a->shape);
	const auto bCircle = std::static_pointer_cast<Circle>(b->shape);

	const Vec2 ab = b->position - a->position;

	const bool collision = ab.MagnitudeSquared() < pow(aCircle->radius + bCircle->radius, 2);

	if(!collision) return collision;

	contact.a = a;
	contact.b = b;

	contact.normal = ab.UnitVector();

	contact.start = b->position - contact.normal * bCircle->radius;
	contact.end = a->position + contact.normal * aCircle->radius;

	contact.depth = (contact.end - contact.start).Magnitude();

	return true;
}
