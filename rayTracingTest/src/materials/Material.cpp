#include "Material.h"

Material::Material(Vector3D amb, Vector3D dif, Vector3D spe, double shi, double ref) : ambient{ amb }, diffuse{ dif }, specular{ spe }, shininess{ shi }, reflection{ ref } {

}

Vector3D& Material::getAmbient() {
	return ambient;
}

Vector3D& Material::getDiffuse() {
	return diffuse;
}

Vector3D& Material::getSpecular() {
	return specular;
}

double Material::getShininess() {
	return shininess;
}

double Material::getReflection() {
	return reflection;
}

Vector3D Material::getAmbient(const Vector3D& point) {
	return ambient;
}

Vector3D Material::getDiffuse(const Vector3D& point) {
	return diffuse;
}

Vector3D Material::getSpecular(const Vector3D& point) {
	return specular;
}

double Material::getShininess(const Vector3D& point) {
	return shininess;
}

double Material::getReflection(const Vector3D& point) {
	return reflection;
}