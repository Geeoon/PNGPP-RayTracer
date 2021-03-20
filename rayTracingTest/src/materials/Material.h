#pragma once
#include "../vector/Vector3D.h"

class Material {
public:
	Material(Vector3D amb, Vector3D dif, Vector3D spe);
	Material(Vector3D amb, Vector3D dif, Vector3D spe, Vector3D inh);
	Material(Vector3D amb, Vector3D dif, Vector3D spe, double shi, double ref);
	Material(Vector3D amb, Vector3D dif, Vector3D spe, double shi, double ref, double refr, double n);
	Material(Vector3D amb, Vector3D dif, Vector3D spe, Vector3D inh, double shi, double ref);
	Material(Vector3D amb, Vector3D dif, Vector3D spe, Vector3D inh, double shi, double ref, double refr, double n);
	Vector3D& getInherent();
	Vector3D& getAmbient();
	Vector3D& getDiffuse();
	Vector3D& getSpecular();
	double getShininess();
	double getReflection();
	double getRefraction();
	double getIndex();
	virtual Vector3D getInherent(const Vector3D& point);
	virtual Vector3D getAmbient(const Vector3D& point);
	virtual Vector3D getDiffuse(const Vector3D& point);
	virtual Vector3D getSpecular(const Vector3D& point);
	virtual double getShininess(const Vector3D& point);
	virtual double getReflection(const Vector3D& point);
	virtual double getRefraction(const Vector3D& point);
	virtual double getIndex(const Vector3D& point);

protected:
	Vector3D ambient, diffuse, specular, inherent;
	double shininess, reflection, refraction, index;
};