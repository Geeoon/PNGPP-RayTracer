#include "PointLight.h"

PointLight::PointLight(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp) : Light{ pos, am, di, sp } {

}

PointLight::PointLight(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double in) : Light{ pos, am, di, sp, in } {

}

double PointLight::getIntensityAt(Vector3D point) {
	return intensity / (Vector3D::magnitude(position - point));
}