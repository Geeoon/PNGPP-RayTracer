#include "Plane.h"

Plane::Plane(Vector3D pos, std::unique_ptr<Material> mat) : Object{ pos, std::move(mat) }, orientation{ Vector3D{ 0, 1, 0 } } {

}

Plane::Plane(Vector3D pos, Vector3D orien, std::unique_ptr<Material> mat) : Object{ pos, std::move(mat) }, orientation{ Vector3D::normalize(orien) } {

}

Vector3D Plane::getNormal(const Vector3D& intersection, const Ray& ray) {
	double denom = ray.direction * orientation;
	if (denom < 1e-6) {
		return orientation;
	}
	return -orientation;
}

double Plane::intersects(const Ray& ray) {
	double denom = ray.direction * orientation;
	if (abs(denom) <= 1e-6) {
		return -1.0;
	} else {
		double t = ((position - ray.position) * orientation) / denom;
		if (t < 0) {
			return -1.0;
		}
		return t;
	}
	
}