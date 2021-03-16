#include "Sphere.h"
Sphere::Sphere(double rad, Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double sh, double re) : radius{ rad }, Object { pos, am, di, sp, sh, re }  {

}

Vector3D Sphere::getNormal(const Vector3D& intersection) {
	return Vector3D::normalize(intersection - position);
}

double Sphere::intersects(const Ray& ray) {
	double b = 2 * (ray.direction * (ray.position - position));
	double c = Vector3D::magnitudeSquared(ray.position - position) - radius * radius;
	double delta = b * b - 4 * c;
	if (delta > 0) {
		double t1 = (-b + sqrt(delta)) / 2;
		double t2 = (-b - sqrt(delta)) / 2;
		if (t1 > 0 && t2 > 0) {
			if (t1 > t2) {
				return t2;
			} else {
				return t1;
			}
		}
	}
	return -1.0;
}