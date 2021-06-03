#pragma once
#include "Object.h"

class Box : public Object {
public:
	Box(Vector3D pos, std::unique_ptr<Material> mat, Vector3D s, Vector3D orien);
	Vector3D getNormal(const Vector3D& intersection, const Ray& ray) override;
	double intersects(const Ray& ray) override;

private:
	Vector3D size, orientation;
};