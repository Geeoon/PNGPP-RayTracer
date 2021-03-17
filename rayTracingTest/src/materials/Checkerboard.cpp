#include "Checkerboard.h"

Checkerboard::Checkerboard(Vector3D amb, Vector3D dif, Vector3D spe, double shi, double ref) : Material{ amb, dif, spe, shi, ref } {

}

Vector3D Checkerboard::getAmbient(const Vector3D& point) {
	if (ceil(sin(point.x) * sin(point.z)) == 0) {
		return ambient;
	} else {
		return Vector3D{ 0, 0, 0 };
	}
}

Vector3D Checkerboard::getDiffuse(const Vector3D& point) {
	if (ceil(sin(point.x) * sin(point.z)) == 0) {
		return diffuse;
	} else {
		return Vector3D{ 0, 0, 0 };
	}
}

Vector3D Checkerboard::getSpecular(const Vector3D& point) {
	return specular;
}

double Checkerboard::getShininess(const Vector3D& point) {
	return shininess;
}

double Checkerboard::getReflection(const Vector3D& point) {
	return reflection;
}