#pragma once
#include "../vector/Vector3D.h"

class Material {
public:
	Material(Vector3D amb, Vector3D dif, Vector3D spe, double shi, double ref);
	Material(Vector3D amb, Vector3D dif, Vector3D spe, double shi, double ref, Vector3D inh);
	Vector3D& getInherent();
	Vector3D& getAmbient();
	Vector3D& getDiffuse();
	Vector3D& getSpecular();
	double getShininess();
	double getReflection();
	virtual Vector3D getAmbient(const Vector3D& point);
	virtual Vector3D getDiffuse(const Vector3D& point);
	virtual Vector3D getSpecular(const Vector3D& point);
	virtual double getShininess(const Vector3D& point);
	virtual double getReflection(const Vector3D& point);

protected:
	Vector3D ambient, diffuse, specular, inherent;
	double shininess, reflection;
};