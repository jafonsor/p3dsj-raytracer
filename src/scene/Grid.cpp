#include "Grid.h"

#include <iostream>
#include <cmath>
#include <glm.hpp>


Voxel::Voxel(int x, int y, int z)
	: _x(x), _y(y), _z(z), _objects()
{
	// empty
}

int Voxel::x() { return _x; }
int Voxel::y() { return _y; }
int Voxel::z() { return _z; }
void Voxel::addObject(Object * obj) {
	_objects.push_back(obj);
}

bool Voxel::operator>(Voxel &other) {
	if(x() > other.x()) {
		return true;
	} else if(x() == other.x() && y() > other.y()) {
		return true;
	} else if(y() == other.y() && z() > other.z()) {
		return true;
	} else {
		return false;
	}
}

Intersection * Voxel::checkIntersection(Ray * ray) {
	std::list<Object*>::iterator it;
	Intersection * result = nullptr;
	Intersection * intersectionPoint;
	float minDist = FLT_MAX;
	for (it = _objects.begin(); it != _objects.end(); it++) {
		intersectionPoint = (*it)->checkIntersection(ray);
		if (intersectionPoint != nullptr && intersectionPoint->distanceToEye < minDist) {
			delete result;
			result = intersectionPoint;
			minDist = result->distanceToEye;
		}
	}
	return result;
}

std::list<Object*> Voxel::getObjects() {
	return _objects;
}

Grid::Grid(float voxelLength)
	: _voxelLength(voxelLength), _boundingBox(), _voxels()
{
	// empty
}

int Grid::convertToGridCoord(float coord) {
	return (int)ceil(coord / _voxelLength);
}

void Grid::addObject(Object *obj) {
	glm::vec3 maxCorner = obj->getMaxCorner();
	glm::vec3 minCorner = obj->getMinCorner();

	_boundingBox.updateMaxCorner(maxCorner);
	_boundingBox.updateMinCorner(minCorner);

	int maxX = convertToGridCoord(maxCorner.x);
	int maxY = convertToGridCoord(maxCorner.y);
	int maxZ = convertToGridCoord(maxCorner.z);

	int minX = convertToGridCoord(minCorner.x);
	int minY = convertToGridCoord(minCorner.y);
	int minZ = convertToGridCoord(minCorner.z);

	for(int x = minX; x <= maxX; x++) {
		for(int y = minY; y <= maxY; y++) {
			for(int z = minZ; z <= maxZ; z++) {
				addVoxel(x,y,z, obj);
			}
		}
	}
}

// If the voxel exists add the object to the voxels object list.
// Otherwise insert a new voxel on the voxels list on an ordered way.
void Grid::addVoxel(int x, int y, int z, Object * obj) {
	Voxel * existantVoxel = getVoxel(x,y,z);
	if(existantVoxel != nullptr) {
		existantVoxel->addObject(obj);
	} else {
		Voxel * newVoxel = new Voxel(x, y, z);
		newVoxel->addObject(obj);
		std::list<Voxel*>::iterator it;
		if(_voxels.empty()) {
			_voxels.push_back(newVoxel);
		} else {
			for(it = _voxels.begin(); it != _voxels.end(); it++) {
				if(*(*it) > *newVoxel) {
					_voxels.insert(it,newVoxel);
					break;
				}
			}
			_voxels.push_back(newVoxel);
		}
	}
}

Voxel * Grid::getVoxel(int x, int y, int z) {
	std::list<Voxel*>::iterator it;
	for(it = _voxels.begin(); it != _voxels.end(); it++) {
		if((*it)->x() == x 
			&& (*it)->y() == y
			&& (*it)->z() == z)
		{
			return (*it);
		}
	}
	return nullptr;
}

BoundingBox Grid::boundingBoxForVoxel(int x, int y, int z) {
	int xmin = (x-1) * _voxelLength;
	int ymin = (y-1) * _voxelLength;
	int zmin = (z-1) * _voxelLength;

	int xmax = xmin + _voxelLength;
	int ymax = ymin + _voxelLength;
	int zmax = zmin + _voxelLength;

	BoundingBox voxelBox(
		glm::vec3(xmin,ymin,zmin),
		glm::vec3(xmax,ymax,zmax)
	);
	return voxelBox;
}

Intersection * Grid::TraverseGrid(int x, int y, int z, Ray * ray) {
	intersection *  result = nullptr;

	int stepx = (ray->direction.x > 0) ? 1 : -1;
	int stepy = (ray->direction.y > 0) ? 1 : -1;
	int stepz = (ray->direction.z > 0) ? 1 : -1;

	int justOutX = (stepx > 0) ? convertToGridCoord(_boundingBox.getMaxCorner().x) + 1 : convertToGridCoord(_boundingBox.getMinCorner().x) - 1;
	int justOutY = (stepy > 0) ? convertToGridCoord(_boundingBox.getMaxCorner().y) + 1 : convertToGridCoord(_boundingBox.getMinCorner().y) - 1;
	int justOutZ = (stepz > 0) ? convertToGridCoord(_boundingBox.getMaxCorner().z) + 1 : convertToGridCoord(_boundingBox.getMinCorner().z) - 1;

	BoundingBox voxelBox = boundingBoxForVoxel(x, y, z);
	float tMaxX, tDeltaX;
	float tMaxY, tDeltaY;
	float tMaxZ, tDeltaZ;
	voxelBox.tMaxAndTDeltaX(ray, &tMaxX, &tDeltaX);
	voxelBox.tMaxAndTDeltaY(ray, &tMaxY, &tDeltaY);
	voxelBox.tMaxAndTDeltaZ(ray, &tMaxZ, &tDeltaZ);
	do {
		Voxel * voxel = getVoxel(x, y, z);
		if (voxel != nullptr) {
			result = voxel->checkIntersection(ray);
		}
		if (result != nullptr)
			return result;

		if (tMaxX < tMaxY) {
			if (tMaxX < tMaxZ) {
				x = x + stepx;
				if (x >= justOutX) {
					return nullptr;
				}
				tMaxX += tDeltaX;
			} else {
				z += stepz;
				if (z >= justOutZ) {
					return nullptr;
				}
				tMaxZ += tDeltaZ;
			}
		} else {
			if (tMaxY < tMaxZ) {
				y += stepy;
				if (y >= justOutY) {
					return nullptr;
				}
				tMaxY += tDeltaY;
			} else {
				z += stepz;
				if (z >= justOutZ) {
					return nullptr;
				}
				tMaxZ += tDeltaZ;
			}
		}
	} while (result == nullptr);
	return result;
}

Intersection * Grid::checkIntersection(Ray * ray) {
	float epsilon = 1E-3;
	Intersection * inter = _boundingBox.checkIntersection(ray);
	if(inter == nullptr) return nullptr;
	
	int x;
	int y;
	int z;

	if (_boundingBox.insideBounds(ray->point)) {
		x = convertToGridCoord(ray->point.x);
		y = convertToGridCoord(ray->point.y);
		z = convertToGridCoord(ray->point.z);
	}
	else {
		x = convertToGridCoord(inter->position.x + ray->direction.x * epsilon);
		y = convertToGridCoord(inter->position.y + ray->direction.y * epsilon);
		z = convertToGridCoord(inter->position.z + ray->direction.z * epsilon);
	}

	TraverseGrid(x,y,z,ray);
} 