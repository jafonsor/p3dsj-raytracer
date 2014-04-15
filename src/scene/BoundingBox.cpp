#include "BoundingBox.h"
#include "Plane.h"
#include <iostream>

BoundingBox::BoundingBox()
	: _minCorner(), _maxCorner()
{
	// emtpy
}

BoundingBox::BoundingBox(glm::vec3 minCorner, glm::vec3 maxCorner)
	: _minCorner(minCorner), _maxCorner(maxCorner)
{
	// empty
}

void BoundingBox::setDimentions(glm::vec3 & minCorner, glm::vec3 & maxCorner) {
	_minCorner = minCorner;
	_maxCorner = maxCorner;
}

Plane BoundingBox::posPlaneX() {
	Plane posx(
		glm::vec3(_maxCorner.x, 0, 0),
		glm::vec3(1,0,0)
	);
	return posx;
}

Plane BoundingBox::negPlaneX() {
	Plane negx(
		glm::vec3(_minCorner.x, 0, 0),
		glm::vec3(-1,0,0)
	);
	return negx;
}

Plane BoundingBox::posPlaneY() {
	Plane posy(
		glm::vec3(0, _maxCorner.y, 0),
		glm::vec3(0,1,0)
	);
	return posy;
}

Plane BoundingBox::negPlaneY() {
	Plane negy(
		glm::vec3(0, _minCorner.y, 0),
		glm::vec3(0,-1,0)
	);
	return negy;
}

Plane BoundingBox::posPlaneZ() {
	Plane posz(
		glm::vec3(0, 0, _maxCorner.z),
		glm::vec3(0,0,1)
	);
	return posz;
}

Plane BoundingBox::negPlaneZ() {
	Plane negz(
		glm::vec3(0, 0, _minCorner.z),
		glm::vec3(0,0,-1)
	);
	return negz;
}

Intersection * BoundingBox::checkIntersection(Ray * ray) {
	// create the planes of the box
	Plane posx = posPlaneX();
	Plane negx = negPlaneX();
	Plane posy = posPlaneY();
	Plane negy = negPlaneY();
	Plane posz = posPlaneZ();
	Plane negz = negPlaneZ();

	Plane planes[] = {posx,negx,posy,negy,posz,negz};

	// Check plane by plane if the intersections with the ray
	Intersection * minInter = nullptr;
	for(int i = 0; i < 6; i++) {
		Intersection * inter = planes[i].checkIntersection(ray);
		// Check if the intersection position is within the dimentions of
		// the bounding box.
		if(inter != nullptr && insideBounds(inter->position)) {

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

bool BoundingBox::insideBounds(glm::vec3 p) {
	return p.x <= _maxCorner.x && p.y <= _maxCorner.y && p.z <= _maxCorner.z
	       && p.x >= _minCorner.x && p.y >= _minCorner.y && p.z <= _maxCorner.z;
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

// the tMax and the tDelta are the return variables
void tMaxAndTDelta(Plane posPlane, Plane negPlane, Ray *ray, float *tMax, float *tDelta) {
	Intersection * posInter = posPlane.checkIntersection(ray);
	Intersection * negInter = negPlane.checkIntersection(ray);

	if(posInter == nullptr || negInter == nullptr) {
		std::cout << "BoundingBox.cpp, tmax: Can not calculate tMax for a ray that doesn't intersect the voxel" << std::endl;
		return;
	}

	if(posInter->distanceToEye > negInter->distanceToEye) {
		*tMax = posInter->distanceToEye;
	} else {
		*tMax = negInter->distanceToEye;
	}

	*tDelta = abs(posInter->distanceToEye - negInter->distanceToEye);
}

void BoundingBox::tMaxAndTDeltaX(Ray *ray, float *tMaxX, float *tDeltaX) {
	tMaxAndTDelta(posPlaneX(),negPlaneX(),ray,tMaxX,tDeltaX);
}

void BoundingBox::tMaxAndTDeltaY(Ray *ray, float *tMaxY, float *tDeltaY) {
	tMaxAndTDelta(posPlaneY(),negPlaneY(),ray,tMaxY,tDeltaY);
}

void BoundingBox::tMaxAndTDeltaZ(Ray *ray, float *tMaxZ, float *tDeltaZ) {
	tMaxAndTDelta(posPlaneZ(),negPlaneZ(),ray,tMaxZ,tDeltaZ);
}

glm::vec3 BoundingBox::getMaxCorner() {
	return _maxCorner;
}

glm::vec3 BoundingBox::getMinCorner() {
	return _minCorner;
}