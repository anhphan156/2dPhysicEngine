#include <math.h>
#include <iostream>
#include <memory>
#include "CollisionDetection.h"
#include "Body.h"
#include "Contact.h"
#include "Vec2.h"

bool CollisionDetection::CollisionDetection(std::shared_ptr<Body> a, std::shared_ptr<Body> b, Contact& contact){
	ShapeType aShapeType = a->shape->GetShape();
	ShapeType bShapeType = b->shape->GetShape();

	if(aShapeType == CIRCLE && bShapeType == CIRCLE){
		return CollisionDetectionCircleCircle(a, b, contact);			
	}

	if((aShapeType == BOX || aShapeType == POLYGON) && (bShapeType == BOX || bShapeType == POLYGON)){
		return CollisionDetectionPolygonPolygon(a, b, contact);
	}

	return false;
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

bool CollisionDetection::CollisionDetectionPolygonPolygon(std::shared_ptr<Body> a, std::shared_ptr<Body> b, Contact& contact){
	const std::shared_ptr<Polygon> aPolygon = std::static_pointer_cast<Polygon>(a->shape);
	const std::shared_ptr<Polygon> bPolygon = std::static_pointer_cast<Polygon>(b->shape);

	Vec2 aAxis;
	Vec2 aPoint;
	const float aSeparation = aPolygon->FindMinSeparation(bPolygon, aAxis, aPoint);

	Vec2 bAxis;
	Vec2 bPoint;
	const float bSeparation = bPolygon->FindMinSeparation(aPolygon, bAxis, bPoint);

	if(aSeparation >= 0.f || bSeparation >= 0.f) return false;

	contact.a = a;
	contact.b = b;
	if(aSeparation > bSeparation){
		contact.depth = -aSeparation;
		contact.normal = aAxis.Normal();
		contact.start = aPoint;
		contact.end = aPoint + contact.normal * contact.depth;
	} else {
		contact.depth = -bSeparation;
		contact.normal = -bAxis.Normal();
		contact.end = bPoint;
		contact.start = bPoint - contact.normal * contact.depth;
	}
	
	return true;
}
