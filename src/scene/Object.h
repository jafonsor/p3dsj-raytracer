#ifndef OBJECT_H
#define OBJECT_H

#include "Geometry.h"

typedef struct color {
	float r, g, b
} Color;

class Object {
	Geometry * _geometry;

public:
	Color _color;

	Object(Color * color, Geometry * geometry);
	Object(float r, float g, float b, Geometry * geometry);

	Point * checkIntersection(Ray * ray);
};

#endif