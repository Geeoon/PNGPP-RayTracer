#include "PointLight.h"

PointLight::PointLight(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double dropOff) : Light{ pos, am, di, sp }, dropOffValue{ dropOff } {

}

PointLight::PointLight(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double dropOff, double in) : Light{ pos, am, di, sp, in }, dropOffValue{ dropOff } {

}

double PointLight::getIntensityAt(Vector3D point) {
	return intensity / (Vector3D::magnitude(position - point) * dropOffValue);
}