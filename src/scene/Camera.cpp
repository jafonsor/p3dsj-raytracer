#include"Camera.h"

Camera::Camera(glm::vec3 eye, glm::vec3 at, glm::vec3 up, float fovy, int resX, int resY) : eye(eye), at(at), up(up), fovy(fovy), _resX(resX), _resY(resY) {
	init();
}

void Camera::init() {
	ze = eye - at;
	df = glm::length(ze);
	ze = glm::normalize(ze);

	h = 2 * df * tan(fovy / 2);
	w = (_resX / _resY) * h;

	xe = glm::cross(up, ze);
	xe = glm::normalize(xe);

	ye = glm::cross(ze, xe);
}

Ray Camera::getPrimaryRay(int x, int y) {
	Ray ray;
	glm::vec3 direction = -df * ze + h * ((y / (_resY - 1.0f)) - 0.5f) * ye + w * ((x / (_resX - 1.0f)) - 0.5f) * xe;
	ray.point = eye;
	ray.direction = glm::normalize(direction);
	return ray;
}

glm::vec3 Camera::getEye() {
	return eye;
}

int Camera::resX() {
	return _resX;
}

int Camera::resY() {
	return _resY;
}