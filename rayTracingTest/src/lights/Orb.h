#pragma once
#include "../objects/Sphere.h"
#include "PointLight.h"
class Orb : public PointLight, public Sphere {
public:
	Orb(Vector3D pos, std::unique_ptr<Material>& mat, Vector3D inh);
	Orb(Vector3D pos, std::unique_ptr<Material>& mat, Vector3D inh, double dropOff);
	Orb(Vector3D pos, std::unique_ptr<Material>& mat, Vector3D inh, double dropOff, double in);;

private:

};