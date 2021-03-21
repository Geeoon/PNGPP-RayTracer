#pragma once
#include "vector/Vector3D.h"
#include "vector/Vector4D.h"

class Camera {
public:
	Camera(Vector3D pos, Vector3D ori, double r);
	Camera(Vector3D pos, Vector3D ori, double r, double z);
	Vector3D position, orientation;
	double ratio, zoom;
	Vector4D screen;

};

