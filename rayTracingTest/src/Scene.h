#pragma once
#include <memory>
#include <vector>
#include "objects/Object.h"
#include "lights/Light.h"
#include "Camera.h"

class Scene {
public:
	Scene(std::unique_ptr<Camera> cam);
	void addLight(std::unique_ptr<Light> l);
	void addObject(std::unique_ptr<Object> obj);
	std::unique_ptr<Camera>& getCamera();
	std::vector<std::unique_ptr<Light>>& getLights();
	std::vector<std::unique_ptr<Object>>& getObjects();

private:
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<Light>> lights;
	std::vector<std::unique_ptr<Object>> objects;
};

