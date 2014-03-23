#include "Plane.h"
#include "Intersection.h"

Plane::Plane(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
	_normal = glm::normalize( glm::cross(  v1 - v0, v2 - v0 ) );
	_d = - glm::dot( v0, _normal );
}

#define DELTA 0.00001

Intersection * Plane::checkIntersection(Ray * ray) {
	float dotNormalDirection = glm::dot(_normal, ray->direction);
	if( -DELTA < dotNormalDirection && dotNormalDirection < DELTA ) {
		// the ray is parallel to the plane
		return nullptr;
	} else {
		float auxA = _d + glm::dot( _normal, ray->point );
		float t = -  auxA / dotNormalDirection;
		Intersection * intersection = new Intersection;
		intersection->position = ray->f(t);
		intersection->normal   = _normal;
		intersection->distanceToEye = t;
		return intersection;
	}
}