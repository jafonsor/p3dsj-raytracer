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
	~Voxel();
	int x();
	int y();
	int z();
	void addObject(Object *);
	bool operator>(Voxel &other);
	Intersection * checkIntersection(Ray * ray);
};


class Grid {
	float _voxelLength;
	BoundingBox _boundingBox;
	std::list<Voxel*> _voxels;

	void addVoxel(int x, int y, int z, Object * obj);
	Voxel * getVoxel(int x, int y, int z);

public:
	Grid(float voxelLength = 1.0f);
	~Grid();

	// Converts a coordenate to the grid coordenate.
	// It's the same for all axis because voxels are cubes.
	int convertToGridCoord(float coord);

	// Add the object to the the voxels the object belongs.
	void addObject(Object *obj);
	BoundingBox boundingBoxForVoxel(int x, int y, int z);
	Intersection * checkIntersection(Ray * ray);
};

#endif