#ifndef CAMERA_H
#define CAMERA_H

#include<glm.hpp>
#include"Ray.h"

#define PI  3.1415926535897f

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
	Ray getPrimaryRay(float x, float y);
	glm::vec3 getEye();
	int resX();
	int resY();
	float getDf();
	glm::vec3 getXe();
	glm::vec3 getYe();
	glm::vec3 getZe();
};


#endif