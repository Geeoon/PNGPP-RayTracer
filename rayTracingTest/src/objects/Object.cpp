#include "Object.h"
Object::Object(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double sh, double re) : position{ pos }, ambient{ am }, diffuse{ di }, specular{ sp }, shininess{ sh }, reflection{ re } {

}

Vector3D& Object::getPosition() {
	return position;
}

Vector3D& Object::getAmbient() {
	return ambient;
}

Vector3D& Object::getDiffuse() {
	return diffuse;
}

Vector3D& Object::getSpecular() {
	return specular;
}

double Object::getShininess() {
	return shininess;
}

double Object::getReflection() {
	return reflection;
}