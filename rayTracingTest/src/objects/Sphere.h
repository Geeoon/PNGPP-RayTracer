#pragma once
#include <cmath>
#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(double rad, Vector3D pos, Material mat);
	Vector3D getNormal(const Vector3D& intersection, const Ray& ray) override;
	double intersects(const Ray& ray) override;

private:
	double radius;
};

