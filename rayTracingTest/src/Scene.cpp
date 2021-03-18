#include "Scene.h"

Scene::Scene(std::unique_ptr<Camera> cam) : camera{ std::move(cam) } {

}

void Scene::addLight(std::unique_ptr<Light> l) {
	lights.push_back(std::move(l));
}

void Scene::addObject(std::unique_ptr<Object> obj) {
	objects.push_back(std::move(obj));
}

std::unique_ptr<Camera>& Scene::getCamera() {
	return camera;
}

std::vector<std::unique_ptr<Light>>& Scene::getLights() {
	return lights;
}

std::vector<std::unique_ptr<Object>>& Scene::getObjects() {
	return objects;
}