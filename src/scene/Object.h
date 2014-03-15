#ifndef OBJECT_H
#define OBJECT_H

#include "Geometry.h"

typedef struct color {
	float r, g, b
} Color;

class Object {
	Color _color;
	Geometry * _geometry;

public:

	Object(Color * color, Geometry * geometry);
	Object(float r, float g, float b, Geometry * geometry);

	Color * getColor();

	Point * checkIntersection(Ray * ray);
};

#endif