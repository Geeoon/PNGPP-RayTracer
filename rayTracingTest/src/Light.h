#pragma once
#include "vector/Vector3D.h"

class Light
{
public:
	Light(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp);
	Vector3D position, ambient, diffuse, specular;

};

