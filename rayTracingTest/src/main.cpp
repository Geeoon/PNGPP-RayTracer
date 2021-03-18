#include <png++/png.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Renderer.h"
#include "Scene.h"
#include "materials/Checkerboard.h"
#include "materials/Material.h"
#include "vector/Vector4D.h"
#include "vector/Vector3D.h"
#include "objects/Plane.h"
#include "objects/Object.h"
#include "objects/Sphere.h"
#include "lights/PointLight.h"
#include "lights/Light.h"

#define M_PI 3.14159265358979323846264338327950288

int main() {
	const double maxDist = DBL_MAX;
	const unsigned int maxReflects = 5;
	unsigned int width{ 400 };
	unsigned int height{ 400 };
	double ratio{ static_cast<double>(width) / height };
	Scene sceneRoom{ std::make_unique<Camera>(Vector3D{ 0, 8, -15 }, Vector3D{ 0, 0, 0 }, ratio) };
	sceneRoom.addLight(std::make_unique<PointLight>(Vector3D{ 0.0, 19, 5.0 }, std::make_unique<Material>(Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, 50, 0), .1, 2.0));
	sceneRoom.addObject(std::make_unique<Sphere>(2, Vector3D{ 0, 2, 5 }, std::make_unique<Material>(Vector3D{ 0.1, 0.0, 0.0 }, Vector3D{ 0.7, 0.0, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5)));
	sceneRoom.addObject(std::make_unique<Sphere>(2, Vector3D{ 5, 2, 5 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.1 }, Vector3D{ 0.0, 0.0, 0.7 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5)));
	sceneRoom.addObject(std::make_unique<Sphere>(2, Vector3D{ -5, 2, 5 }, std::make_unique<Material>(Vector3D{ 0.0, 0.1, 0.0 }, Vector3D{ 0.0, 0.6, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5)));
	sceneRoom.addObject(std::make_unique<Sphere>(5, Vector3D{ 0, 5, 12 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 100.0, 1)));
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, 25 }, Vector3D{ 0, 0, -1 }, std::make_unique<Material>(Vector3D{ 0.1, 0.0, 0.0 }, Vector3D{ 0.3, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // front wall
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ -25, 0, 0 }, Vector3D{ 1, 0, 0 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.1 }, Vector3D{ 0.0, 0.0, 0.3 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // left wall
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ 25, 0, 0 }, Vector3D{ -1, 0, 0 }, std::make_unique<Material>(Vector3D{ 0.0, 0.1, 0.0 }, Vector3D{ 0.0, 0.3, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // right wall
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, -25 }, Vector3D{ 0, 0, 1 }, std::make_unique<Material>(Vector3D{ 0.1, 0.1, 0.1 }, Vector3D{ 0.3, 0.3, 0.3 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // back wall
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, 0 }, Vector3D{ 0, 1, 0 }, std::make_unique<Checkerboard>(Vector3D{ 0.4, 0.4, 0.4 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0.1, 0.1, 0.1 }, 0, .10, 3)));  // floor
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ 0, 20, 0 }, Vector3D{ 0, -1, 0 }, std::make_unique<Material>(Vector3D{ 0.2, 0.2, .2 }, Vector3D{ .3, .3, .3 }, Vector3D{ 0, 0, 0 }, 50, 0)));  // ceiling
	/*
	Camera camera{ Vector3D{ 0, 8, -15 }, Vector3D{ 0, 0, 0 }, ratio};
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Light>> lights;
	objects.push_back(std::make_unique<Sphere>(2, Vector3D{ 0, 2, 5 }, std::make_unique<Material>(Vector3D{ 0.1, 0.0, 0.0 }, Vector3D{ 0.7, 0.0, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5)));
	objects.push_back(std::make_unique<Sphere>(2, Vector3D{ 5, 2, 5 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.1 }, Vector3D{ 0.0, 0.0, 0.7 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5)));
	objects.push_back(std::make_unique<Sphere>(2, Vector3D{ -5, 2, 5 }, std::make_unique<Material>(Vector3D{ 0.0, 0.1, 0.0 }, Vector3D{ 0.0, 0.6, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5)));
	objects.push_back(std::make_unique<Sphere>(5, Vector3D{ 0, 5, 12 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 100.0, 1)));
	objects.push_back(std::make_unique<Plane>(Vector3D{ 0, 0, 25 }, Vector3D{ 0, 0, -1 }, std::make_unique<Material>(Vector3D{ 0.1, 0.0, 0.0 }, Vector3D{ 0.3, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // front wall
	objects.push_back(std::make_unique<Plane>(Vector3D{ -25, 0, 0 }, Vector3D{ 1, 0, 0 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.1 }, Vector3D{ 0.0, 0.0, 0.3 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // left wall
	objects.push_back(std::make_unique<Plane>(Vector3D{ 25, 0, 0}, Vector3D{ -1, 0, 0 }, std::make_unique<Material>(Vector3D{ 0.0, 0.1, 0.0 }, Vector3D{ 0.0, 0.3, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // right wall
	objects.push_back(std::make_unique<Plane>(Vector3D{ 0, 0, -25}, Vector3D{ 0, 0, 1 }, std::make_unique<Material>(Vector3D{ 0.1, 0.1, 0.1 }, Vector3D{ 0.3, 0.3, 0.3 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // back wall
	objects.push_back(std::make_unique<Plane>(Vector3D{ 0, 0, 0 }, Vector3D{ 0, 1, 0 }, std::make_unique<Checkerboard>(Vector3D{ 0.4, 0.4, 0.4 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0.1, 0.1, 0.1 }, 0, .10, 3)));  // floor
	//objects.push_back(std::make_unique<Plane>(Vector3D{ 0, 101, 0 }, std::make_unique<Material>(Vector3D{ 0.85, 0.91, 1 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0, 0, 0 }, 0, 0)));  // sky outside
	objects.push_back(std::make_unique<Plane>(Vector3D{ 0, 20, 0 }, Vector3D{ 0, -1, 0 }, std::make_unique<Material>(Vector3D{ 0.2, 0.2, .2 }, Vector3D{ .3, .3, .3 }, Vector3D{ 0, 0, 0 }, 50, 0)));  // ceiling inside
	
	//lights.push_back(std::make_unique<Light>(Vector3D{ 100.0, 100.0, -100.0 }, Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }));  // sun
	lights.push_back(std::make_unique<PointLight>(Vector3D{ 0.0, 19, 5.0 }, std::make_unique<Material>(Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, 50, 0), .1, 2.0));  // ceiling light
	//objects.push_back(std::make_unique<Plane>(Vector3D{ 0, 19.1, 5 }, Vector3D{ 0, -1, 0 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0, 0, 0 }, 0, 0)));  // light blocker (prevents light from hitting ceiling) has to be a box, not a plane
	*/

	Renderer renderer{};
	png::image<png::rgb_pixel_16>& image = renderer.render(maxReflects, width, height, sceneRoom);

	image.write("output.png");
	return 0;
}