#pragma once
#include <cmath>
#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(double rad, Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double sh, double re);
	double intersects(const Ray& ray) override;

private:
	double radius;
};

