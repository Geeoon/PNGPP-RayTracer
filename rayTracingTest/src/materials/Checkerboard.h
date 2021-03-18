#pragma once
#include "Material.h"

class Checkerboard : public Material {
public:
	Checkerboard(Vector3D amb, Vector3D dif, Vector3D spe, double shi, double ref, double til);  // for use on flat planes
	Vector3D getAmbient(const Vector3D& point) override;
	Vector3D getDiffuse(const Vector3D& point) override;
	Vector3D getSpecular(const Vector3D& point) override;
	double getShininess(const Vector3D& point) override;
	double getReflection(const Vector3D& point) override;

private:
	double tiling;
};