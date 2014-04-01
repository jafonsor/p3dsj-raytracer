#include <cstdlib> // abs
#include "RecursiveAntialising.h"

RecursiveAntialising::RecursiveAntialising(PixelDrawer * wrappedDrawer, int maxDepth)
	:_wrappedDrawer(wrappedDrawer), _maxDepth(maxDepth)
{
	// empty
}

inline glm::vec3 RecursiveAntialising::drawPixel(float x, float y) {
	return overSample(x, y, 1);
}

// returns the contrast between colors c1 and c2
float contrast(glm::vec3 c1, glm::vec3 c2);

glm::vec3 RecursiveAntialising::overSample(float x, float y, int depth) {
	float delta = 1/(depth+1);
	glm::vec3 color1 = _wrappedDrawer->drawPixel(      x,      y);
	glm::vec3 color2 = _wrappedDrawer->drawPixel(x+delta,      y);
	glm::vec3 color3 = _wrappedDrawer->drawPixel(      x,y+delta);
	glm::vec3 color4 = _wrappedDrawer->drawPixel(x+delta,y+delta);

	// thresholds
	float t12 = contrast(color1,color2);
	float t13 = contrast(color1,color3);
	float t14 = contrast(color1,color4);
	float t23 = contrast(color2,color3);
	float t24 = contrast(color2,color4);
	float t34 = contrast(color3,color4);

	float threshold = (t12 + t13 + t14 + t23 + t24 + t34) / 6;

	if(threshold < 0.3 || depth >= _maxDepth) {
		return (color1 + color2 + color3 + color4) / 4.0f;
	} else {
		int   nextDepth = depth - 1;
		float nextDelta = 1/(nextDepth+1);
		glm::vec3 color1 = overSample(          x,          y,nextDepth);
		glm::vec3 color2 = overSample(x+nextDelta,          y,nextDepth);
		glm::vec3 color3 = overSample(          x,y+nextDelta,nextDepth);
		glm::vec3 color4 = overSample(x+nextDelta,y+nextDelta,nextDepth);
		return (color1 + color2 + color3 + color4) / 4.0f;
	}

}

float contrast(glm::vec3 c1, glm::vec3 c2) {
	return abs(c1.r - c2.r) + abs(c1.g - c2.g) + abs(c1.b - c2.b);
}