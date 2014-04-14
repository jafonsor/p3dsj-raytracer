#include <iostream>
#include <fstream>
#include <string>
#include <glm.hpp>
#include <sstream>
#include "NFFLoader.h"
#include "scene/Scene.h"
#include "scene/Sphere.h"
#include "scene/Light.h"
#include "scene/Plane.h"
#include "scene/Triangle.h"


typedef struct object_properties {
	glm::vec3 color;
	float     kd;
	float     ks;
	float     shininess;
	float     transmittance;
	float     ir;
	object_properties(glm::vec3 color, float kd, float ks, float shininess, float transmittance, float ir)
		: color(color), kd(kd), ks(ks), shininess(shininess), transmittance(transmittance), ir(ir)
	{
		//empty
	}
} ObjectProperties;

glm::vec3 readBackground(std::istream &in);
Camera*   readCamera(std::istream &in);
Light*    readLight(std::istream &in);
ObjectProperties* readObjectProperties(std::istream &in);
Sphere*   readSphere(std::istream &in);
Plane*    readPlane(std::istream &in);
Triangle* readTriangle(std::istream &in);


// -- aux functions

Object * createObject(ObjectProperties * properties, Geometry * geom) {
	if(properties == nullptr) {
		std::cout << "Error loading nff: geometry without properties."  << std::endl;
		exit(0);
	}
	return new Object(
			properties->color,
			properties->kd,
			properties->ks,
			properties->shininess,
			properties->transmittance,
			properties->ir,
			geom
	);
}

const float DEGREE_TO_RAD = PI / 180;
float degToRad(float deg) { return deg * DEGREE_TO_RAD; }

Scene * NFFLoader::createScene(const char * fileName) {
	Scene * scene = new Scene(); // the scene that will be returned
	std::string entity; // used to store the first string of the line
	ObjectProperties * currentProperties = nullptr;

	std::ifstream file;
	file.open(fileName);
	if(file.fail()) {
		std::cout << "Error loading nff: unable to open the file " << fileName << std::endl;
		exit(0);
	}
	const int size = 200;
	char line[size];
	int lineNumber = 0;
	while(!(file >> entity).eof()) {
		lineNumber++;
		if( entity == "b" ) {
			scene->setBackground( readBackground(file) );
		} else if( entity == "v" ) {
			scene->setCamera( readCamera(file) );
		} else if( entity == "l" ) {
			scene->addLight( readLight(file) );
		} else if( entity == "f" ) {
			delete currentProperties;
			currentProperties = readObjectProperties(file);
		} else if( entity == "s" ) {
			Geometry * sphere = readSphere(file);
			scene->addObject( createObject(currentProperties, sphere) );
		} else if( entity == "pl" ) {
			Geometry * plane = readPlane(file);
			scene->addPlane( createObject(currentProperties, plane) );
		} else if( entity == "p" ) {
			Geometry * triangle = readTriangle(file);
			scene->addObject( createObject(currentProperties, triangle) );
		} else if ( entity == "al") {
			//bad programing  not done
			float ux, uy, uz, vx, vy, vz;
			int n;
			Light * light = readLight(file);
			file >> ux >> uy >> uz >> vx >> vy >> vz >> n;
			glm::vec3 u(ux, uy, uz);
			glm::vec3 v(vx, vy, vz);
			scene->addAreaLight(light,u,v,n);
		} else {
			// discard all characters until the end of the line
			char line[200];
			file.getline(line,200);
			std::stringstream lineStream(line);
			std::cout << "NFFLoader: ignored line>" << entity << " " << line << std::endl; 
		}
	}
	return scene;
}

glm::vec3 readBackground(std::istream &in) {
	float r, g, b;
	in >> r >> g >> b;
	return glm::vec3(r, g, b);
}



Camera * readCamera(std::istream &in) {
	float eyeX, eyeY, eyeZ;
	float atX,  atY,  atZ;
	float upX,  upY,  upZ;
	float angle; // flovy in degrees
	float hither; // ignored
	float resX;
	float resY;

	std::string parameter; // ignored

	in >> parameter >> eyeX >> eyeY >> eyeZ;
	in >> parameter >> atX  >> atY  >> atZ;
	in >> parameter >> upX  >> upY  >> upZ;
	in >> parameter >> angle;
	in >> parameter >> hither;
	in >> parameter >> resX  >> resY;

	return new Camera(
		glm::vec3(eyeX, eyeY, eyeZ),
		glm::vec3(atX,  atY,  atZ),
		glm::vec3(upX,  upY,  upZ),
		degToRad(angle),
		resX, resY
	);
}


Light * readLight(std::istream &in) {
	float x, y, z; // light position
	float r, g, b; // light color

	char line[200];
	in.getline(line,200);
	std::stringstream lineStream(line);

	lineStream >> x >> y >> z
	           >> r >> g >> b;

	if(lineStream.fail()) {
		// assume that the failure occurred because the optional
		// color was not there to be read
		return new Light(glm::vec3(x,y,z));
	}
	return new Light(glm::vec3(x,y,z), glm::vec3(r,g,b));
}

ObjectProperties * readObjectProperties(std::istream &in) {
	float r, g, b;
	float kd;
	float ks;
	float shininess;
	float transmittance;
	float ir;

	in >> r >> g >> b >> kd >> ks >> shininess >> transmittance >> ir;

	return new ObjectProperties(
		glm::vec3(r,g,b),
		kd,
		ks,
		shininess,
		transmittance,
		ir
	);
}

Sphere * readSphere(std::istream &in) {
	float cx, cy, cz; // center
	float radius;

	in >> cx >> cy >> cz >> radius;

	return new Sphere(cx,cy,cz, radius);
}

Plane * readPlane(std::istream &in) {
	float v0x, v0y, v0z;
	float v1x, v1y, v1z;
	float v2x, v2y, v2z;

	in >> v0x >> v0y >> v0z
	   >> v1x >> v1y >> v1z
	   >> v2x >> v2y >> v2z;

	return new Plane(
		glm::vec3(v0x, v0y, v0z),
		glm::vec3(v1x, v1y, v1z),
		glm::vec3(v2x, v2y, v2z)
	);
}

Triangle * readTriangle(std::istream &in) {
	int numberOfVertices;
	float v0x, v0y, v0z;
	float v1x, v1y, v1z;
	float v2x, v2y, v2z;

	in >> numberOfVertices; // discarded
	in >> v0x >> v0y >> v0z
	   >> v1x >> v1y >> v1z
	   >> v2x >> v2y >> v2z;

	return new Triangle(
		glm::vec3(v0x, v0y, v0z),
		glm::vec3(v1x, v1y, v1z),
		glm::vec3(v2x, v2y, v2z)
	);
}