#include "Object.h"
Object::Object(Vector3D pos, Material mat) : position{ pos }, material{ mat } {

}

Vector3D& Object::getPosition() {
	return position;
}

Vector3D Object::getNormal(const Vector3D& intersection, const Ray& ray) {
	return Vector3D{ 0, 0, 0 };
}

Material& Object::getMaterial() {
	return material;
}