#include "Object.h"

Object::Object(glm::vec3 color, float kd, float ks, float shininess, Geometry * geometry)
: color(color), kd(kd), ks(ks), shininess(shininess), _geometry(geometry)
{

}

Object::Object(glm::vec3 color, float kd, float ks, float shininess, float transmittance, float indexOfRefraction, Geometry * geometry)
: color(color), kd(kd), ks(ks), shininess(shininess), transmittance(transmittance), indexOfRefraction(indexOfRefraction), _geometry(geometry)
{

}

Intersection * Object::checkIntersection(Ray * ray) {
	Intersection * result = _geometry->checkIntersection(ray);
	if (result != nullptr)
		result->object = this;
	return result;
}

glm::vec3 Object::getMaxCorner() {
	return _geometry->getMaxCorner();
}

glm::vec3 Object::getMinCorner() {
	return _geometry->getMinCorner();
}