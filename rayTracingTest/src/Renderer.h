#pragma once
#include <png++/png.hpp>
#include <vector>
#include <memory>
#include "Scene.h"
#include "vector/Vector4D.h"
#include "vector/Vector3D.h"
#include "objects/Object.h"
#include "lights/Light.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	png::image<png::rgb_pixel_16>& render(unsigned int maxReflects, unsigned int width, unsigned int height, Scene& scene);

private:
	const double maxDist;
	png::image<png::rgb_pixel_16> image;
};

