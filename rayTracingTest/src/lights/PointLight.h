#pragma once
#include "Light.h"

class PointLight : public Light {
public:
	PointLight(Vector3D pos, std::unique_ptr<Material> mat);
	PointLight(Vector3D pos, std::unique_ptr<Material> mat, double dropOff);
	PointLight(Vector3D pos, std::unique_ptr<Material> mat, double dropOff, double in);
	double getIntensityAt(const Vector3D& point) override;
private:
	const double dropOffValue;
};

