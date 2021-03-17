#pragma once
#include "Light.h"

class PointLight : public Light {
public:
	PointLight(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp);
	PointLight(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double in);
	double getIntensityAt(Vector3D point) override;
private:

};

