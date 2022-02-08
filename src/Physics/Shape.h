#ifndef SHAPE_H
#define SHAPE_H
#include <vector>

enum ShapeType {
	CIRCLE, POLYGON, BOX
};

struct Shape {
	ShapeType shapeType;

	Shape() = default;
	~Shape();

	virtual ShapeType GetShape() const = 0;
	virtual float GetMomentOfInertia() const = 0;
};

struct Circle : public Shape {
	float radius;

	Circle(float radius);
	~Circle();

	ShapeType GetShape() const override;
	float GetMomentOfInertia() const override;
};

struct Polygon : public Shape {
	std::vector<class Vec2> localVertices;
	std::vector<class Vec2> worldVertices;

	Polygon() = default;
	~Polygon() = default;

	void UpdateVertices(float angle, Vec2 position);
};

struct Box : public Polygon {
	float width, height;

	Box(float width, float height);
	~Box() = default;

	ShapeType GetShape() const override;
	float GetMomentOfInertia() const override;
};
#endif
