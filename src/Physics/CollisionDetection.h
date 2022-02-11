#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <memory>

struct Body;
struct Contact;

namespace CollisionDetection {

	bool CollisionDetection(std::shared_ptr<Body>, std::shared_ptr<Body>, Contact&);
	bool CollisionDetectionCircleCircle(std::shared_ptr<Body>, std::shared_ptr<Body>, Contact&);
	bool CollisionDetectionPolygonPolygon(std::shared_ptr<Body>, std::shared_ptr<Body>, Contact&);
}

#endif
