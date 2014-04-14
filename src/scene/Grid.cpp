#include "Grid.h"

#include <iostream>
#include <cmath>
#include <glm.hpp>


Voxel::Voxel(int x, int y, int z)
	: _x(x), _y(y), _z(z), _objects()
{
	// empty
}

Voxel::~Voxel() {
	std::list<Object*>::iterator it;
	for(it = _objects.begin(); it != _objects.end(); it++) {
		delete *it;
	}
}

int Voxel::x() { return _x; }
int Voxel::y() { return _y; }
int Voxel::z() { return _z; }
void Voxel::addObject(Object * obj) {
	_objects.push_back(obj);
}

bool Voxel::operator>(Voxel &other) {
	if(x() > other.x()) {
		return false;
	} else if(x() == other.x() && y() > other.y()) {
		return false;
	} else if(y() == other.y() && z() > other.z()) {
		return false;
	} else {
		return true;
	}
}

Intersection * Voxel::checkIntersection(Ray * ray) {
	std::list<Object*>::iterator it;
	Intersection * result;
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

Grid::Grid(float voxelLength)
	: _voxelLength(voxelLength), _boundingBox(), _voxels()
{
	// empty
}

Grid::~Grid() {
	std::list<Voxel*>::iterator it;
	for(it = _voxels.begin(); it != _voxels.end(); it++) {
		delete *it;
	}
}

int Grid::convertToGridCoord(float coord) {
	return (int)floor(coord / _voxelLength);
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
			std::cout << "A voxel was not added" << std::endl;
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
	float maxX;
	BoundingBox voxelBox();
	return
}

Intersection * Grid::checkIntersection(Ray * ray) {
	Intersection * inter = _boundingBox.checkIntersection(ray);
	if(inter == nullptr) return nullptr;

	// initialize
	int x = convertToGridCoord(inter->position.x);
	int y = convertToGridCoord(inter->position.y);
	int z = convertToGridCoord(inter->position.z);

	int stepx = (ray->direction.x > 0)? 1: -1;
	int stepy = (ray->direction.y > 0)? 1: -1;
	int stepz = (ray->direction.z > 0)? 1: -1;

	BoundingBox voxelBox = boundingBoxForVoxel(x,y,z);
	float tMaxX = voxelBox.tMaxX(ray);
	float tMaxY = voxelBox.tMaxY(ray);
	float tMaxZ = voxelBox.tMaxZ(ray);
	
}