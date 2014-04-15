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
	BoundingBox(glm::vec3 minCorner, glm::vec3 maxCorner);
	void setDimentions(glm::vec3 &minCorner, glm::vec3 &maxCorner);
	Intersection * checkIntersection(Ray * ray);

	// Update if necessary the min and max corners to contain the 'corner'
	void updateMaxCorner(glm::vec3 &corner);
	void updateMinCorner(glm::vec3 &corner);

	void tMaxAndTDeltaX(Ray *ray, float *tMaxX, float *tDeltaX);
	void tMaxAndTDeltaY(Ray *ray, float *tMaxY, float *tDeltaY);
	void tMaxAndTDeltaZ(Ray *ray, float *tMaxZ, float *tDeltaZ);

	glm::vec3 getMaxCorner();
	glm::vec3 getMinCorner();

	// Checks if the point is inside the bounding box
	bool insideBounds(glm::vec3 point, int axis = 3);
};

#endif