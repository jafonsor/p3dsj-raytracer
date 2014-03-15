#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "Intersection.h"
#include "Geometry.h"

typedef struct color {
	float r, g, b;
} Color;

class Object {
	Color _color;
	Geometry *_geometry;

public:
	Object(Color * color, Geometry * geometry);
	Object(float r, float g, float b, Geometry * geometry);

	Color * getColor();

	Intersection * checkIntersection(Ray * ray);
};

#endif