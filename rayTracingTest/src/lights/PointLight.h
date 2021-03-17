#pragma once
#include "Light.h"

class PointLight : public Light {
public:
	PointLight(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double dropOff);
	PointLight(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double dropOff, double in);
	double getIntensityAt(const Vector3D& point) override;
private:
	const double dropOffValue;
};

