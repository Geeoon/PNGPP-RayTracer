#include "Object.h"
Object::Object(Vector3D pos, std::unique_ptr<Material> mat) : position{ pos }, material{ std::move(mat) } {

}

Vector3D& Object::getPosition() {
	return position;
}

Vector3D Object::getNormal(const Vector3D& intersection, const Ray& ray) {
	return Vector3D{ 0, 0, 0 };
}

std::unique_ptr<Material>& Object::getMaterial() {
	return material;
}