#include "BoundingBox.h"
#include "Plane.h"

BoundingBox::BoundingBox()
	: _minCorner(), _maxCorner()
{
	// emtpy
}
void BoundingBox::setDimentions(glm::vec3 & minCorner, glm::vec3 & maxCorner) {
	_minCorner = minCorner;
	_maxCorner = maxCorner;
}

Intersection * BoundingBox::checkIntersection(Ray * ray) {
	// create the planes of the box
	Plane posx(
		glm::vec3(_maxCorner.x, 0, 0),
		glm::vec3(1,0,0)
	);

	Plane negx(
		glm::vec3(_minCorner.x, 0, 0),
		glm::vec3(-1,0,0)
	);

	Plane posy(
		glm::vec3(0, _maxCorner.y, 0),
		glm::vec3(0,1,0)
	);

	Plane negy(
		glm::vec3(0, _minCorner.y, 0),
		glm::vec3(0,-1,0)
	);

	Plane posz(
		glm::vec3(0, 0, _maxCorner.z),
		glm::vec3(0,0,1)
	);

	Plane negz(
		glm::vec3(0, 0, _minCorner.z),
		glm::vec3(0,0,-1)
	);

	Plane planes[] = {posx,negx,posy,negy,posz,negz};

	// Check plane by plane if the intersections with the ray
	Intersection * minInter = nullptr;
	for(int i = 0; i < 6; i++) {
		Intersection * inter = planes[i].checkIntersection(ray);
		// Check if the intersection position is within the dimentions of
		// the bounding box.
		if(inter != nullptr
			&& inter->position[i/2] < _maxCorner[i/2]
			&& inter->position[i/2] > _minCorner[i/2])
		{
			// Check if it is the closest intersection
			if(minInter == nullptr 
			   || minInter->distanceToEye > inter->distanceToEye)
			{
				minInter = inter;
			} else {
				delete inter;
			}
		} else if(inter != nullptr) {
			delete inter;
		}
	}

	return minInter;
}

void BoundingBox::updateMaxCorner(glm::vec3 &corner) {
	float newMaxX = _maxCorner.x;
	float newMaxY = _maxCorner.y;
	float newMaxZ = _maxCorner.z;

	if(corner.x > _maxCorner.x) {
		newMaxX = corner.x;
	}
	if(corner.y > _maxCorner.y) {
		newMaxY = corner.y;
	}
	if(corner.z > _maxCorner.z) {
		newMaxZ = corner.z;
	}

	_maxCorner = glm::vec3(newMaxX,newMaxY,newMaxZ);
}

void BoundingBox::updateMinCorner(glm::vec3 &corner) {
	float newMinX = _minCorner.x;
	float newMinY = _minCorner.y;
	float newMinZ = _minCorner.z;

	if(corner.x < _minCorner.x) {
		newMinX = corner.x;
	}
	if(corner.y < _minCorner.y) {
		newMinY = corner.y;
	}
	if(corner.z < _minCorner.z) {
		newMinZ = corner.z;
	}

	_minCorner = glm::vec3(newMinX,newMinY,newMinZ);
}