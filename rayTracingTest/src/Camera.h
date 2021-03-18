#pragma once
#include "vector/Vector3D.h"
#include "vector/Vector4D.h"

class Camera {
public:
	Camera(Vector3D pos, Vector3D ori, double r);
	Vector3D position, orientation;
private:
	double ratio;
	Vector4D screen;
};

