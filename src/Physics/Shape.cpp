#include "Shape.h"
#include <iostream>
#include "Vec2.h"


// Shape
Shape::~Shape(){
	std::cout << "Shape destroyed"  << std::endl;
}

// Circle
Circle::Circle(float radius)
	: radius(radius)
{

}

Circle::~Circle(){
	std::cout << "Circle destroyed"  << std::endl;
}

ShapeType Circle::GetShape() const {
	return CIRCLE;
}

float Circle::GetMomentOfInertia() const {
	return .5f * (radius * radius);
}

// Polygon
void Polygon::UpdateVertices(float angle, Vec2 position){
	for(unsigned int i = 0; i < worldVertices.size(); i++){
		worldVertices[i] = localVertices[i].Rotate(angle);
		worldVertices[i] += position;
	}
}

// Box
Box::Box(float width, float height)
:	width(width), height(height){

	localVertices.push_back(Vec2(-width / 2, -height / 2));	
	localVertices.push_back(Vec2(+width / 2, -height / 2));	
	localVertices.push_back(Vec2(+width / 2, +height / 2));	
	localVertices.push_back(Vec2(-width / 2, +height / 2));	

	worldVertices.push_back(Vec2(-width / 2, -height / 2));	
	worldVertices.push_back(Vec2(+width / 2, -height / 2));	
	worldVertices.push_back(Vec2(+width / 2, +height / 2));	
	worldVertices.push_back(Vec2(-width / 2, +height / 2));	
}

ShapeType Box::GetShape() const {
	return BOX;
}

float Box::GetMomentOfInertia() const {
	return (width * width + height * height) / 12.f;
}
