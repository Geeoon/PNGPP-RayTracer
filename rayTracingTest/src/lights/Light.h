#pragma once
#include <memory>
#include "../materials/Material.h"
#include "../vector/Vector3D.h"

class Light
{
public:
	Light(Vector3D pos, std::unique_ptr<Material> mat);
	Light(Vector3D pos, std::unique_ptr<Material> mat, double in);
	virtual double getIntensityAt(const Vector3D& point);
	std::unique_ptr<Material>& getMaterial();
	Vector3D position;
	double intensity;

private:
	std::unique_ptr<Material> material;
};

