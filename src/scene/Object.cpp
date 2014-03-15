#include "Object.h"

Object::ObjectObject(Color * color, Geometry * geometry)
	: _geometry(geometry)
{
	_color.r = color.r;
	_color.g = color.g;
	_color.b = color.b;
}

Object::Object(float r, float g, float b, Geometry * geometry)
	: _geometry(geometry)
{
	_color.r = r;
	_color.g = g;
	_color.b = b;
}

Color * Object::getColor() {
	return &_color;
}

Point * Object::checkIntersection(Ray * ray) {
	return _geometry->checkIntersection(ray);
}