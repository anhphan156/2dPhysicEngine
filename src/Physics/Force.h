#ifndef FORCE_H
#define FORCE_H

#include "Vec2.h"
#include "Body.h"

namespace Force{
	Vec2 GenerateDragForce(Body&, float strength);
	Vec2 GenerateSpringForce(const Body& body, const Vec2& anchor, float restLength, float k);

};
#endif
