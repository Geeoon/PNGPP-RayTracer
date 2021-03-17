#include "Plane.h"

Plane::Plane(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double sh, double re) : Object{ pos, am, di, sp, sh, re } {

}

Vector3D Plane::getNormal(const Vector3D& intersection, const Ray& ray) {
	if (ray.direction.y < 0) {
		return Vector3D{ 0, 1, 0 };
	} else {
		return Vector3D{ 0, -1, 0 };
	}
}

double Plane::intersects(const Ray& ray) {
	if ((ray.direction.y > 0 && ray.position.y > position.y) || (ray.direction.y < 0 && ray.position.y < position.y) || (ray.direction.y == 0)) {
		return -1.0;
	} else {
		Vector3D point{ 0, position.y, 0 };
		double deltay = position.y - ray.position.y;
		point.x = ray.position.x + (ray.direction.x / ray.direction.y * deltay);
		point.z = ray.position.z + (ray.direction.z / ray.direction.y * deltay);
		return Vector3D::magnitude(ray.position - point);
	}
}