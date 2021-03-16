#pragma once
#include "Vector3D.h"

class Ray
{
public:
	Ray(Vector3D pos, Vector3D dir);
	Vector3D position, direction;
};

