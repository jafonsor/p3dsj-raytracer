#ifndef CAMERA_H
#define CAMERA_H

#include<glm.hpp>
#include"Ray.h"

class Camera {
private:
	glm::vec3 eye, up, at;
	glm::vec3 xe, ye, ze;
	float fovy;
	float w, h, df;
	int _resX, _resY;
public:
	Camera(glm::vec3 eye,glm::vec3 at,glm::vec3 up,float fovy, int resX,int resY);
	void init();
	Ray getPrimaryRay(int x, int y);
	glm::vec3 getEye();
	int resX();
	int resY();
};


#endif