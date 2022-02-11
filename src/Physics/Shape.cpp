#include "Shape.h"
#include <iostream>
#include <limits>
#include "Vec2.h"

// Shape
Shape::~Shape(){
	//std::cout << "Shape destroyed"  << std::endl;
}

// Circle
Circle::Circle(float radius)
	: radius(radius)
{

}

Circle::~Circle(){
	//std::cout << "Circle destroyed"  << std::endl;
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

Vec2 Polygon::EdgeAt(unsigned int index) const {
	const Vec2 a = worldVertices[index];
	const Vec2 b = worldVertices[(index + 1) % worldVertices.size()];

	return b - a;
}
float Polygon::FindMinSeparation(const std::shared_ptr<Polygon> other, Vec2& OUT_axis, Vec2& OUT_point) const {
	float separation = std::numeric_limits<float>().lowest();

	for(unsigned int i = 0; i < this->worldVertices.size(); i++){
		float minSep = std::numeric_limits<float>().max();
		const Vec2 va = this->worldVertices[i];
		const Vec2 edge = this->EdgeAt(i);
		const Vec2 normal = edge.Normal();
		Vec2 otherPoint;

		for(unsigned int j = 0; j < other->worldVertices.size(); j++){
			const Vec2 vb = other->worldVertices[j];
			float proj = normal.Dot(vb - va);
			//std::cout 
				//<< i << " " << j << " " 
				//<< normal.x << " " << normal.y << " " 
				//<< "va " << va.x << " " << va.y << " " 
				//<< "vb " << vb.x << " " << vb.y << " " 
				//<< "vb - va "<< (vb - va).x << " " << (vb - va).y << " " 
				//<< "proj " << proj 
				//<< std::endl;
			if(proj < minSep){
				minSep = proj;
				otherPoint = other->worldVertices[j];
			}
		}

		if(minSep > separation){
			separation = minSep;
			OUT_axis = edge;
			OUT_point = otherPoint;
		}
	}

	return separation;
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
