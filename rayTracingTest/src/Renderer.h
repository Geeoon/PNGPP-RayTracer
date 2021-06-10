#pragma once
#include <iostream>
#include <png++/png.hpp>
#include <random>
#include <vector>
#include <thread>
#include <future>
#include <memory>
#include <array>
#include "vector/Vector4D.h"
#include "vector/Vector3D.h"
#include "objects/Object.h"
#include "lights/Light.h"
#include "Camera.h"
#include "Scene.h"

#define M_PI 3.14159265358979323846264338327950288

class Renderer
{
public:
	Renderer();
	png::image<png::rgb_pixel_16>& render(unsigned int maxReflects, unsigned int width, unsigned int height, Scene& scene);
	png::image<png::rgb_pixel_16>& renderMultithread(unsigned int maxReflects, unsigned int width, unsigned int height, Scene& scene);
	png::image<png::rgb_pixel_16>& renderPathTracing(unsigned int maxReflects, unsigned int width, unsigned int height, Scene& scene, unsigned int samples);

private:
	Vector3D BlinnPhong(std::unique_ptr<Object>* obj, std::unique_ptr<Camera>& cam, const Vector3D& lightVector, const Vector3D& normalVector, const Vector3D& intersection, std::unique_ptr<Light>& light);
	Vector3D tracePath(Ray& ray, Scene& scene, double index, unsigned int depth, unsigned int maxReflects);
	Vector3D refract(double n1, double n2, const Vector3D& normal, const Vector3D& incident);
	Vector3D renderRay(Scene& scene, double maxReflects, const Ray& r);
	std::vector<std::vector<Vector3D>> renderSection(unsigned int maxReflects, unsigned int width, unsigned int height, unsigned int start, unsigned int end, Vector4D& screen, Scene& scene);
	void renderRay(Scene& scene, double maxReflects, const Ray& r, Vector3D* output);  // stores value in output instead of returning it.
	Vector3D randomUnitVector3D();
	double reflectanceFresnel(double n1, double n2, const Vector3D& normal, const Vector3D& incident);
	double calculateSchlick(double n1, double n2, const Vector3D& normal, const Vector3D& incident);	
	unsigned int threadCount = 8;
	const double maxDist;
	std::mt19937_64 mt_engine;
	std::uniform_real_distribution<double> theta_d;
	std::uniform_real_distribution<double> z_d;
	std::uniform_real_distribution<double> u_d;
	png::image<png::rgb_pixel_16> image;
};

