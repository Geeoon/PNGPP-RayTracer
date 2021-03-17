#pragma once
#include "../vector/Vector3D.h"

class Light
{
public:
	Light(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp);
	Light(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double in);
	virtual double getIntensityAt(Vector3D point);
	Vector3D position, ambient, diffuse, specular;
	double intensity;

	Light operator/(double factor) const {
		return Light{ position, ambient / factor, diffuse / factor, specular / factor };
	}
};

