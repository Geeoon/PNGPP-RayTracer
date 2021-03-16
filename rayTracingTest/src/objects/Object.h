#pragma once
#include <vector>
#include <memory>
#include "../vector/Vector3D.h"
#include "../vector/Ray.h"

class Object {
public:
	Object(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double sh, double re);
	Vector3D& getPosition();
	Vector3D& getAmbient();
	Vector3D& getDiffuse();
	Vector3D& getSpecular();
	virtual Vector3D getNormal(const Vector3D& intersection);
	double getShininess();
	double getReflection();
	virtual double intersects(const Ray& ray) {
		return 0;
	}

	static Vector3D reflected(const Vector3D& vector, const Vector3D& axis) {
		return vector - axis * 2 * (vector * axis);
	}

	static std::unique_ptr<Object>* nearestObject(std::vector<std::unique_ptr<Object>>& objVect, double& dist, const Ray& ray) {
		std::unique_ptr<Object>* nearestObj{ nullptr };

		for (size_t i = 0; i < objVect.size(); i++) {
			double tempDist{ objVect[i]->intersects(ray) };
			if (tempDist != -1.0 && tempDist < dist) {
				dist = tempDist;
				nearestObj = &objVect[i];
			}
		}
		return nearestObj;
	}

protected:
	Vector3D position, ambient, diffuse, specular;
	double shininess, reflection;
};