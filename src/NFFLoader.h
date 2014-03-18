#ifndef NFF_LOADER_H
#define NFF_LOADER_H


#include <string>

class Scene;

class NFFLoader {
public:
	static Scene * createScene(char * fileName);
};

#endif