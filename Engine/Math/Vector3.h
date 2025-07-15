#pragma once

#include <cmath>

namespace swaws
{
	template <typename T>
	struct Vector3
	{
		T x, y, z;

		Vector3() = default;
		Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

		// Operators added by GitHub Copilot

		// Addition
		Vector3 operator+(const Vector3& rhs) const {
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}
		Vector3& operator+=(const Vector3& rhs) {
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		// Subtraction
		Vector3 operator-(const Vector3& rhs) const {
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}
		Vector3& operator-=(const Vector3& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		// Multiplication (element-wise)
		Vector3 operator*(const Vector3& rhs) const {
			return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		// Division (element-wise)
		Vector3 operator/(const Vector3& rhs) const {
			return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
		}

		// Length between this and another vector
		float length(const Vector3& other) const {
			float dx = static_cast<float>(x - other.x);
			float dy = static_cast<float>(y - other.y);
			float dz = static_cast<float>(z - other.z);
			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}
	};

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}