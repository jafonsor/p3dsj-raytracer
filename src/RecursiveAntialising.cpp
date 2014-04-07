#include <iostream>
#include <cstdlib> // abs
#include "RecursiveAntialising.h"

RecursiveAntialising::RecursiveAntialising(PixelDrawer * wrappedDrawer, int maxDepth)
	:_wrappedDrawer(wrappedDrawer), _maxDepth(maxDepth), _depthCounter(maxDepth)
{
	// empty
}

inline glm::vec3 RecursiveAntialising::drawPixel(float x, float y) {
	return overSample(x, y, 1);
}

// returns the difference between colors c1 and c2
float diff(glm::vec3 c1, glm::vec3 c2);

// Calculate the color in the middle of ci and df.
glm::vec3 interpolateMiddleColor(glm::vec3 ci, glm::vec3 cf);


glm::vec3 RecursiveAntialising::overSample(float x, float y, int depth) {
	_depthCounter[depth-1]++; // for profiling reasons
	float delta = 1.0f/(depth+1.0f);
	glm::vec3 color1 = _wrappedDrawer->drawPixel(      x,      y);
	glm::vec3 color2 = _wrappedDrawer->drawPixel(x+delta,      y);
	glm::vec3 color3 = _wrappedDrawer->drawPixel(      x,y+delta);
	glm::vec3 color4 = _wrappedDrawer->drawPixel(x+delta,y+delta);

	// threshold
	glm::vec3 rightMiddleColor = interpolateMiddleColor(color1,color3);
	glm::vec3 leftMiddleColor  = interpolateMiddleColor(color2,color4);
	float threshold = diff(rightMiddleColor,leftMiddleColor);

	if(threshold < 3.0f || depth >= _maxDepth) {
		return (color1 + color2 + color3 + color4) / 4.0f;
	} else {
		int   nextDepth = depth + 1;
		float nextDelta = 1/(nextDepth+1);
		glm::vec3 color1 = overSample(          x,          y,nextDepth);
		glm::vec3 color2 = overSample(x+nextDelta,          y,nextDepth);
		glm::vec3 color3 = overSample(          x,y+nextDelta,nextDepth);
		glm::vec3 color4 = overSample(x+nextDelta,y+nextDelta,nextDepth);
		return (color1 + color2 + color3 + color4) / 4.0f;
	}

}

float diff(glm::vec3 c1, glm::vec3 c2) {
	return abs(c1.r - c2.r) + abs(c1.g - c2.g) + abs(c1.b - c2.b);
}


// Calculate the color in the middle of ci and df.
glm::vec3 interpolateMiddleColor(glm::vec3 ci, glm::vec3 cf) {
	float rm = (ci.r - cf.r) / 2 + ci.r;
	float gm = (ci.g - cf.g) / 2 + ci.g;
	float bm = (ci.b - cf.b) / 2 + ci.b;
	return glm::vec3(rm,gm,bm);
}

void RecursiveAntialising::print() {
	std::cout << "Antialising stats:" << std::endl;
	for(int i = 0; i < _maxDepth; i++) {
		std::cout << "depth " << i+1 << ": " << _depthCounter[i] << std::endl;
	}
	_wrappedDrawer->print();
}