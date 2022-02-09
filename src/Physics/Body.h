#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vec2.h"
#include <memory>
#include "Shape.h"

struct Body {
	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;

	Vec2 netForce;

	float rotation;
	float angularVelocity;
	float angularAcceleration;

	float netTorque;

	float mass;
	float invMass;
	float I; // moment of inertia
	float invI;

	float restitution;

	std::shared_ptr<Shape> shape;

	Body(float x, float y, float mass, std::shared_ptr<Shape> shape);
	~Body();

	void AddForce(const Vec2&);
	void ClearForce();

	void AddTorque(float);
	void ClearTorque();

	void Integrate(float);
	void IntegrateTorque(float);

	void BodyUpdate(float);

	bool IsStatic() const;

	void ApplyImpulse(const Vec2&);
};

#endif
