#include "Body.h"
#include <iostream>
#include <memory>

Body::Body(float x, float y, float mass, std::shared_ptr<Shape> shape){
	this->position = Vec2(x, y);
	this->velocity = Vec2(0.f, 0.f);
	this->acceleration = Vec2(0.f, 0.f);
	this->mass = mass;

	this->shape = shape;
	this->rotation = 0.f;
	this->angularVelocity = 0.f;
	this->angularAcceleration = 0.f;
	this->I = this->shape->GetMomentOfInertia() * mass;

	this->netForce = Vec2(0.f, 0.f);
	this->netTorque = 0.f;

	this->invMass = mass != 0.f ? 1 / mass : 0.f;
	this->invI = I != 0.f ? 1 / I : 0.f;
}

Body::~Body(){
	//std::cout << "Body destroyed" << std::endl;
}

void Body::Integrate(float dt){
	acceleration = netForce * invMass;	

	velocity += acceleration * dt;
	position += velocity * dt;

	ClearForce();	
}

void Body::IntegrateTorque(float dt){
	angularAcceleration = netTorque * invI;

	angularVelocity += angularAcceleration * dt;
	rotation += angularVelocity * dt;

	ClearTorque();
}

void Body::ClearForce(){
	netForce = Vec2(0.f, 0.f);
}

void Body::ClearTorque(){
	netTorque = 0.f;
}

void Body::AddForce(const Vec2& force){
	netForce += force;
}

void Body::AddTorque(float torque){
	this->netTorque += torque;
}

void Body::BodyUpdate(float dt){
	if(!IsStatic()) {
		Integrate(dt);
		IntegrateTorque(dt);
	}

	const ShapeType shapeType = this->shape->GetShape();
	if(shapeType == BOX || shapeType == POLYGON){
		const auto polygon = std::static_pointer_cast<Polygon>(this->shape);
		polygon->UpdateVertices(this->rotation, this->position);
	}
}

bool Body::IsStatic() const {
	const float epsilon = .005f;
	return (invMass - 0.f) < epsilon;
}

void Body::ApplyImpulse(const Vec2& j){
	if(IsStatic()) return;

	this->velocity += j * invMass; 
}
