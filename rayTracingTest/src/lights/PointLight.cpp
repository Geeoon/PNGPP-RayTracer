#include "PointLight.h"

PointLight::PointLight(Vector3D pos, std::unique_ptr<Material> mat) : Light{ pos, std::move(mat) }, dropOffValue{ 1.0 } {

}
PointLight::PointLight(Vector3D pos, std::unique_ptr<Material> mat, double dropOff) : Light{ pos, std::move(mat) }, dropOffValue{ dropOff } {

}

PointLight::PointLight(Vector3D pos, std::unique_ptr<Material> mat, double dropOff, double in) : Light{ pos, std::move(mat), in }, dropOffValue{ dropOff } {

}

double PointLight::getIntensityAt(const Vector3D& point) {
	return intensity / (Vector3D::magnitude(position - point) * dropOffValue);
}