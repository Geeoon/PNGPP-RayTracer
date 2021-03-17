#include <png++/png.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Renderer.h"
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
	std::vector<std::unique_ptr<Object>> objects;
	objects.push_back(std::make_unique<Sphere>(2, Vector3D{ 0, 0, 4 }, Vector3D{ 0.1, 0.0, 0.0 }, Vector3D{ 0.7, 0.0, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5));
	objects.push_back(std::make_unique<Sphere>(2, Vector3D{ 5, 0, 4 }, Vector3D{ 0.1, 0.0, 0.1 }, Vector3D{ 0.7, 0.0, 0.7 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5));
	objects.push_back(std::make_unique<Sphere>(2, Vector3D{ -5, 0, 4 }, Vector3D{ 0.0, 0.1, 0.0 }, Vector3D{ 0.0, 0.6, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5));
	objects.push_back(std::make_unique<Plane>(Vector3D{ 0, -2, 0 }, Vector3D{ 0.4, 0.4, 0.4 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0.1, 0.1, 0.1 }, 0, 0));  // floor
	objects.push_back(std::make_unique<Plane>(Vector3D{ 0, 101, 0 }, Vector3D{ 0.85, 0.91, 1 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0, 0, 0 }, 0, 0));  // sky
	
	std::vector<std::unique_ptr<Light>> lights;
	
	//lights.push_back(std::make_unique<Light>(Vector3D{ 100.0, 100.0, -100.0 }, Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }));
	lights.push_back(std::make_unique<PointLight>(Vector3D{ 0.0, 0.5, 0.0 }, Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, 2.5));

	Vector3D cameraPosition{ 0, 1, -5 };
	Vector3D cameraAngle{ 0, 0, 0 };  //in radians


	Renderer renderer{};
	png::image<png::rgb_pixel_16> image = renderer.render(maxReflects, width, height, objects, lights, cameraPosition, cameraAngle);

	image.write("output.png");
	return 0;
}