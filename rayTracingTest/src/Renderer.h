#pragma once
#include <png++/png.hpp>
#include <vector>
#include <memory>
#include "vector/Vector4D.h"
#include "vector/Vector3D.h"
#include "objects/Object.h"
#include "Light.h"

class Renderer
{
public:
	Renderer();
	png::image<png::rgb_pixel_16>& render(unsigned int maxReflects, unsigned int width, unsigned int height, std::vector<std::unique_ptr<Object>>& objects, std::vector<std::unique_ptr<Light>>& lights, Vector3D cameraPosition, Vector3D cameraAngle);

private:
	const double maxDist;
	png::image<png::rgb_pixel_16> image;
};

