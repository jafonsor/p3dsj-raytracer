#include <iostream>
#include <fstream>
#include <string>
#include "NFFLoader.h"
#include "scene/Scene.h"
#include <glm.hpp>

glm::vec3 readBackground(std::ifstream &file);
Camera*   readCamera(std::ifstream &file);

std::ios_base& removeString(std::ios_base& in) {
	std::string str;
	in >> str;
	std::cout << "Ignoring: " << str << std::endl;
	return in;
}

Scene * NFFLoader::createScene(char * fileName) {
	glm::vec3 backgroundColor;
	Camera * camera;
	std::string entity; // used to store the first string of the line
	std::ifstream file;
	file.open(fileName);
	while(!file.eof()) {
		file >> entity;
		if( entity == "b" ) {
			backgroundColor = readBackground(file);
		} else if( entity == "v" ) {
			camera = readCamera(file);
		}
	}

}

glm::vec3 readBackground(std::ifstream &file) {
	float r, g, b;
	file >> removeString >> r >> g >> b;
	return glm::vec3(r, g, b);
}

Camera * readCamera(std::ifstream &file) {
	float eyeX, eyeY, eyeZ;
	float atX,  atY,  atZ;
	float upX,  upY,  upZ;
	float angle;
	float hither; // ignored
	float resX;
	float resY;

	file >> eyeX >> eyeY >> eyeZ;
	file >> atX  >> atY  >> atZ;
	file >> upX  >> upY  >> upZ;
	file >> angle;
	file >> hither;
	file >> resX  >> resY;

	return new Camera(
		glm::vec3(eyeX, eyeY, eyeZ),
		glm::vec3(atX,  atY,  atZ),
		glm::vec3(upX,  upY,  upZ),
		angle,
		resX, resY
	);
}