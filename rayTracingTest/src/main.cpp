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
	const unsigned int maxReflects = 500;
	unsigned int width{ 200 };
	unsigned int height{ 200 };
	double ratio{ static_cast<double>(width) / height };
	Scene sceneRoom{ std::make_unique<Camera>(Vector3D{ 0, 8, -15 }, Vector3D{ 0, 0, 0 }, ratio) };
	sceneRoom.addLight(std::make_unique<PointLight>(Vector3D{ 0.0, 19, 5.0 }, std::make_unique<Material>(Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, 50, 0), 1, 400.0));
	sceneRoom.addObject(std::make_unique<Sphere>(2, Vector3D{ 0, 2, 5 }, std::make_unique<Material>(Vector3D{ 0.1, 0.0, 0.0 }, Vector3D{ 0.7, 0.0, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5)));
	sceneRoom.addObject(std::make_unique<Sphere>(2, Vector3D{ 5, 2, 5 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.1 }, Vector3D{ 0.0, 0.0, 0.7 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5)));
	sceneRoom.addObject(std::make_unique<Sphere>(2, Vector3D{ -5, 2, 5 }, std::make_unique<Material>(Vector3D{ 0.0, 0.1, 0.0 }, Vector3D{ 0.0, 0.6, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5)));
	sceneRoom.addObject(std::make_unique<Sphere>(5, Vector3D{ 0, 5, 12 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 100.0, 1)));
	sceneRoom.addObject(std::make_unique<Sphere>(2, Vector3D{ -8, 5, 2 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 0.0, 0.0, 1.0, 1.6)));  // refraction test
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, 25 }, Vector3D{ 0, 0, -1 }, std::make_unique<Material>(Vector3D{ 0.1, 0.0, 0.0 }, Vector3D{ 0.3, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // front wall
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ -25, 0, 0 }, Vector3D{ 1, 0, 0 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.1 }, Vector3D{ 0.0, 0.0, 0.3 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // left wall
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ 25, 0, 0 }, Vector3D{ -1, 0, 0 }, std::make_unique<Material>(Vector3D{ 0.0, 0.1, 0.0 }, Vector3D{ 0.0, 0.3, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // right wall
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, -25 }, Vector3D{ 0, 0, 1 }, std::make_unique<Material>(Vector3D{ 0.1, 0.1, 0.1 }, Vector3D{ 0.3, 0.3, 0.3 }, Vector3D{ 0.0, 0.0, 0.0 }, 50, 0)));  // back wall
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, 0 }, Vector3D{ 0, 1, 0 }, std::make_unique<Checkerboard>(Vector3D{ 0.4, 0.4, 0.4 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0.1, 0.1, 0.1 }, 0, .10, 3)));  // floor
	sceneRoom.addObject(std::make_unique<Plane>(Vector3D{ 0, 20, 0 }, Vector3D{ 0, -1, 0 }, std::make_unique<Material>(Vector3D{ 0.02, 0.02, .02 }, Vector3D{ .0, .0, .0 }, Vector3D{ 0, 0, 0 }, 50, 0)));  // ceiling

	Scene storm{ std::make_unique<Camera>(Vector3D{ 0, 8, -15 }, Vector3D{ 0, 0, 0 }, ratio) };
	storm.addLight(std::make_unique<Light>(Vector3D{ 0, 300, 0 }, std::make_unique<Material>(Vector3D{ 0.18431372549, 0.27058823529, 0.36470588235 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0, 0, 0 }), 1.0));  // ambient light from sky
	//storm.addLight(std::make_unique<PointLight>(Vector3D{ 6, 1, 0 }, std::make_unique<Material>(Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }, Vector3D{ .85, .91, 1.0 }), .5, 1.5));
	storm.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, 0 }, std::make_unique<Checkerboard>(Vector3D{ 0.1, 0.1, 0.1 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0.1, 0.1, 0.1 }, 0, 0, 3)));  // ground
	storm.addObject(std::make_unique<Plane>(Vector3D{ 0, 310, 0 }, Vector3D{ 0, -1, 0 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.18431372549 / 2, 0.27058823529 / 2, 0.36470588235 / 2 })));  // sky
	storm.addObject(std::make_unique<Sphere>(4, Vector3D{ 0, 4, 0 }, std::make_unique<Material>(Vector3D{ 0.3, 0.3, 0.3 }, Vector3D{ 0.6, 0.6, 0.6 }, Vector3D{ 0.1, 0.1, 0.1 }, 100, 0.25)));  // sphere

	Scene simple{ std::make_unique<Camera>(Vector3D{ 0, 1, 0 }, Vector3D{ 0, 0, 0 }, ratio) };
	simple.addLight(std::make_unique<Light>(Vector3D{ 0, 300, 0 }, std::make_unique<Material>(Vector3D{ 1, 1, 1 }, Vector3D{ 1, 1, 1 }, Vector3D{ 1, 1, 1 }), 1.0));
	simple.addObject(std::make_unique<Sphere>(2, Vector3D{ 0, 2, 5 }, std::make_unique<Material>(Vector3D{ 0.1, 0.0, 0.0 }, Vector3D{ 0.7, 0.0, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5)));
	simple.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, 10 }, Vector3D{ 0, 1, 0 }, std::make_unique<Checkerboard>(Vector3D{ 0.3, 0.3, 0.3 }, Vector3D{ 0.5, 0.5, 0.5 }, Vector3D{ 0, 0, 0 }, 0, 0.1, 3)));

	Scene refraction{ std::make_unique<Camera>(Vector3D{ 0, 2, 0 }, Vector3D{ 0, 0, 0 }, ratio) };
	refraction.addLight(std::make_unique<Light>(Vector3D{ 0, 300, 0 }, std::make_unique<Material>(Vector3D{ 1, 1, 1 }, Vector3D{ 1, 1, 1 }, Vector3D{ 1, 1, 1 }), 1.0));
	refraction.addObject(std::make_unique<Sphere>(1, Vector3D{ 0, 1.75, 3 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 0.0, 0.0, 1.0, 1.6)));
	refraction.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, 0 }, Vector3D{ 0, 1, 0 }, std::make_unique<Checkerboard>(Vector3D{ 0.3, 0.3, 0.3 }, Vector3D{ 0.5, 0.5, 0.5 }, Vector3D{ 0, 0, 0 }, 0, 0.1, 3)));

	Scene cornell{ std::make_unique<Camera>(Vector3D{ 0, 0, -7.5 }, Vector3D{ 0, 0, 0 }, ratio, 1.0) };
	//cornell.addLight(std::make_unique<Light>(Vector3D{ 0, 300, 0 }, std::make_unique<Material>(Vector3D{ 1, 1, 1 }, Vector3D{ 1, 1, 1 }, Vector3D{ 1, 1, 1 }), 1.0));

	cornell.addLight(std::make_unique<PointLight>(Vector3D{ 0, 4, 0 }, std::make_unique<Material>(Vector3D{ .95, .95, 1.0 }, Vector3D{ .95, .95, 1.0 }, Vector3D{ .95, .95, 1.0 }), 1, 40));
	cornell.addObject(std::make_unique<Plane>(Vector3D{ -7, 0, 0 }, Vector3D{ 1, 0, 0 }, std::make_unique<Material>(Vector3D{ 0.0607 * 3, 0.02 * 3, 0.0251 * 3 }, Vector3D{ 0.0607 * 8, 0.02 * 8, 0.0251 * 8 }, Vector3D{ 0.0, 0.0, 0.0 }, 0, 0)));  // left wall
	cornell.addObject(std::make_unique<Plane>(Vector3D{ 7, 0, 0 }, Vector3D{ -1, 0, 0 }, std::make_unique<Material>(Vector3D{ 0.0122 * 2.5, 0.0271 * 2.5, 0.0431 * 2.5 }, Vector3D{ 0.0122 * 8, 0.0271 * 8, 0.0431 * 8 }, Vector3D{ 0.0, 0.0, 0.0 }, 0, 0)));  // right wall
	cornell.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, 5 }, Vector3D{ 0, 0, -1 }, std::make_unique<Material>(Vector3D{ 0.075, 0.075, 0.075 }, Vector3D{ 0.5, 0.5, 0.5 }, Vector3D{ 0.0, 0.0, 0.0 }, 0, 0)));  // back wall
	cornell.addObject(std::make_unique<Plane>(Vector3D{ 0, 5, 0 }, Vector3D{ 0, -1, 0 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, Vector3D{ 0.0, 0.0, 0.0 }, 0, 0)));  // ceiling
	cornell.addObject(std::make_unique<Plane>(Vector3D{ 0, -5, 0 }, Vector3D{ 0, 1, 0 }, std::make_unique<Material>(Vector3D{ 0.1, 0.1, 0.1 }, Vector3D{ 0.7, 0.7, 0.7 }, Vector3D{ 0.0, 0.0, 0.0 }, 0, 0)));  // floor
	//cornell.addObject(std::make_unique<Sphere>(2, Vector3D{ 2, -3, -2 }, std::make_unique<Material>(Vector3D{ 0.1, 0.1, 0.1 }, Vector3D{ 0.7, 0.7, 0.7 }, Vector3D{ 0.0, 0.0, 0.0 })));
	//cornell.addObject(std::make_unique<Sphere>(2.5, Vector3D{ -1.5, -2.5, 2 }, std::make_unique<Material>(Vector3D{ 0.1, 0.1, 0.1 }, Vector3D{ 0.7, 0.7, 0.7 }, Vector3D{ 0.0, 0.0, 0.0 })));
	cornell.addObject(std::make_unique<Sphere>(2.0, Vector3D{ 3, -3, 0.0 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 0.0, 0.0, 1.0, 1.52)));
	cornell.addObject(std::make_unique<Sphere>(2.0, Vector3D{ -3, -3, 2.5 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0.0, 0.0, 0.0 }, 100.0, 1.0)));

	Scene pathTracing{ std::make_unique<Camera>(Vector3D{ 0, 2, 0 }, Vector3D{ 0, 0, 0 }, ratio, 1.0) };
	//pathTracing.addObject(std::make_unique<Sphere>(2, Vector3D{ 0, 2, 5 }, std::make_unique<Material>(Vector3D{ 0, 0, 0 }, Vector3D{ 0, 0, 0 }, Vector3D{ 1, 1, 1 })));  // glowing object
	pathTracing.addObject(std::make_unique<Sphere>(2, Vector3D{ 0, 3, 5 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0, 0, 0 }, 0.0, 0.25)));  // sphere
	pathTracing.addObject(std::make_unique<Sphere>(0.5, Vector3D{ 1, 0.5, 5 }, std::make_unique<Material>(Vector3D{ 0.0, 0.0, 0.0 }, Vector3D{ 0, 0, 0 }, Vector3D{ 10.0, 10.0, 10.0 }, 0.0, 0.0)));  // glowing orb
	pathTracing.addObject(std::make_unique<Plane>(Vector3D{ 0, 1000, 0 }, Vector3D{ 0, -1, 0 }, std::make_unique<Checkerboard>(Vector3D{ 0, 0, 0 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0.18, 0.27, 0.36 }, 0.0, 0.0, 3)));  // sky
	pathTracing.addObject(std::make_unique<Plane>(Vector3D{ 0, 0, 0 }, Vector3D{ 0, 1, 0 }, std::make_unique<Checkerboard>(Vector3D{ 0.9, 0.9, 0.9 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0, 0, 0 }, 0.0, 0.0, 3)));  // floor

	Renderer renderer{};

	//png::image<png::rgb_pixel_16>& image = renderer.render(maxReflects, width, height, sceneRoom);
	//png::image<png::rgb_pixel_16>& image = renderer.render(maxReflects, width, height, storm);
	//png::image<png::rgb_pixel_16>& image = renderer.render(maxReflects, width, height, simple);
	//png::image<png::rgb_pixel_16>& image = renderer.render(maxReflects, width, height, refraction);
	//png::image<png::rgb_pixel_16>& image = renderer.render(maxReflects, width, height, cornell);
	png::image<png::rgb_pixel_16>& image = renderer.renderPathTracing(3, width, height, pathTracing, 100);

	image.write("output.png");
	return 0;
}