#pragma once
#include <cmath>

struct Vector3D {
public:
	Vector3D();
	
	Vector3D(double x1, double y1, double z1);

	static Vector3D clip(const Vector3D& vector, double min, double max) {
		Vector3D clipped{ vector };
		if (clipped.x > max) {
			clipped.x = max;
		}

		if (clipped.x < min) {
			clipped.x = min;
		}

		if (clipped.y > max) {
			clipped.y = max;
		}

		if (clipped.y < min) {
			clipped.y = min;
		}

		if (clipped.z > max) {
			clipped.z = max;
		}

		if (clipped.z < min) {
			clipped.z = min;
		}
		return clipped;
	}

	static Vector3D normalize(const Vector3D& vector) {
		return Vector3D{ vector.x / magnitude(vector), vector.y / magnitude(vector), vector.z / magnitude(vector) };
	}

	static double magnitude(const Vector3D& vector) {
		return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}

	static double dot(const Vector3D& v1, const Vector3D& v2) {
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}

	static double magnitudeSquared(const Vector3D& vector) {
		return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
	}
	
	static Vector3D rotate(const Vector3D& vector, const Vector3D& rotation) {

	}

	Vector3D multiply(const Vector3D& other) {  // multiply corrosponding
		return Vector3D{ x * other.x, y * other.y, z * other.z };
	}

	Vector3D operator*(int scalar) const {
		return Vector3D{ scalar * x, scalar * y, scalar * z };
	}

	Vector3D operator*(double scalar) const {
		return Vector3D{ scalar * x, scalar * y, scalar * z };
	}

	Vector3D operator/(double scalar) const {
		return Vector3D{ x / scalar, y / scalar, z / scalar };
	}

	Vector3D operator+(const Vector3D& other) const {
		return Vector3D{ x + other.x, y + other.y, z + other.z };
	}
	
	Vector3D operator-(const Vector3D& other) const {
		return Vector3D{ x - other.x, y - other.y, z - other.z };
	}
	
	Vector3D operator-() const {
		return Vector3D{ -x, -y, -z };
	}

	double operator*(const Vector3D& other) const {  // dot product
		return x * other.x + y * other.y + z * other.z;
	}

	bool operator==(Vector3D const& rhs) const {
		return (x == rhs.x && y == rhs.y && z == rhs.z);
	}

	bool operator!=(Vector3D const& rhs) const {
		return !(x == rhs.x && y == rhs.y && z == rhs.z);
	}

	double x, y, z;
};