#include "Light.h"

Light::Light(Vector3D pos, std::unique_ptr<Material> mat) : position{ pos }, material{ std::move(mat) }, intensity{ 1.0 } {

}

Light::Light(Vector3D pos, std::unique_ptr<Material> mat, double in) : position{ pos }, material{ std::move(mat) }, intensity{ in } {

}

double Light::getIntensityAt(const Vector3D& point) {
	return intensity;
}

std::unique_ptr<Material>& Light::getMaterial() {
	return material;
}