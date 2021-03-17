#pragma once
#include "Object.h"

class Plane : public Object {
public:
	Plane(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double sh, double re);
	Vector3D getNormal(const Vector3D& intersection, const Ray& ray) override;
	double intersects(const Ray& ray) override;
private:

};

