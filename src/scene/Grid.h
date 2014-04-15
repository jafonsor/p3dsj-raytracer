#ifndef GRID_H
#define GRID_H

#include <list>
#include "Object.h"
#include "BoundingBox.h"

class Voxel {
	int _x;
	int _y;
	int _z;
	std::list<Object*> _objects;

public:
	Voxel(int x, int y, int z);
	int x();
	int y();
	int z();
	void addObject(Object *);
	bool operator>(Voxel &other);
	Intersection * checkIntersection(Ray * ray);
	std::list<Object*> getObjects();
};


class Grid {
	float _voxelLength;
	BoundingBox _boundingBox;
	std::list<Voxel*> _voxels;

	void addVoxel(int x, int y, int z, Object * obj);

public:
	Grid(float voxelLength = 1.0f);

	// Converts a coordenate to the grid coordenate.
	// It's the same for all axis because voxels are cubes.
	int convertToGridCoord(float coord);
	
	bool pointInsideGrid(glm::vec3 point);
	Intersection * TraverseGrid(int x,int y,int z, Ray * ray);

	Voxel * getVoxel(int x, int y, int z);

	// Add the object to the the voxels the object belongs.
	void addObject(Object *obj);
	BoundingBox boundingBoxForVoxel(int x, int y, int z);
	Intersection * checkIntersection(Ray * ray);
};

#endif