#include "Box.h"

Box::Box(Vector3D pos, std::unique_ptr<Material> mat, Vector3D s, Vector3D orien) : Object(pos, std::move(mat)), size{ s }, orientation{ orien } {

}


// https://ray-tracing-conept.blogspot.com/2015/01/ray-box-intersection-and-normal.html
Vector3D Box::getNormal(const Vector3D& intersection, const Ray& ray) {
	return Vector3D{ 0, 0, 0 };
}

double Box::intersects(const Ray& ray) {
	return -1.0;
}