#pragma once
#include "Object.h"

class Plane : public Object {
public:
	Plane(Vector3D pos, std::unique_ptr<Material> mat);
	Plane(Vector3D pos, Vector3D orien, std::unique_ptr<Material> mat);
	Vector3D getNormal(const Vector3D& intersection, const Ray& ray) override;
	double intersects(const Ray& ray) override;
private:
	Vector3D orientation;
};

