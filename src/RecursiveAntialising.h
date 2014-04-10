#ifndef RECURSIVE_ANTIALISING_H
#define RECURSIVE_ANTIALISING_H

#include <vector>
#include <glm.hpp>
#include "PixelDrawer.h"

class RecursiveAntialising : public PixelDrawer {
	PixelDrawer * _wrappedDrawer;
	int _maxDepth;
	std::vector<int> _depthCounter;
public:
	RecursiveAntialising(PixelDrawer * wrappedDrawer, int maxDepth);
	inline glm::vec3 drawPixel(float x, float y);
private:
	glm::vec3 overSample(float x, float y, int depth);

	void print();
};

#endif