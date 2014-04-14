#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Geometry.h"
#include "Plane.h"

class BoundingBox : Geometry {
	glm::vec3 _minCorner;
	glm::vec3 _maxCorner;

	Plane negPlaneX();
	Plane posPlaneX();
	Plane negPlaneY();
	Plane posPlaneY();
	Plane negPlaneZ();
	Plane posPlaneZ();

public:
	BoundingBox();
	void setDimentions(glm::vec3 &minCorner, glm::vec3 &maxCorner);
	Intersection * checkIntersection(Ray * ray);

	// Update if necessary the min and max corners to contain the 'corner'
	void updateMaxCorner(glm::vec3 &corner);
	void updateMinCorner(glm::vec3 &corner);
	
	Intersection * tMaxX(Ray *ray);
	Intersection * tMaxY(Ray *ray);
	Intersection * tMaxZ(Ray *ray);

	void tMaxAndTDeltaX(Ray *ray, float &tMaxX, float &tDeltaX);
	void tMaxAndTDeltaY(Ray *ray, float &tMaxY, float &tDeltaY);
	void tMaxAndTDeltaZ(Ray *ray, float &tMaxZ, float &tDeltaZ);
};

#endif