#pragma once

#include <cmath>

namespace swaws
{
	template <typename T>
	struct Vector3
	{
		T r, g, b;

		Vector3() = default;
		Vector3(T r, T g, T b) : r{ r }, g{ g }, b{ b } {}

		// Operators added by GitHub Copilot

		// Addition
		Vector3 operator+(const Vector3& rhs) const {
			return Vector3(r + rhs.r, g + rhs.g, b + rhs.b);
		}
		Vector3& operator+=(const Vector3& rhs) {
			r += rhs.r;
			g += rhs.g;
			b += rhs.b;
			return *this;
		}

		// Subtraction
		Vector3 operator-(const Vector3& rhs) const {
			return Vector3(r - rhs.r, g - rhs.g, b - rhs.b);
		}
		Vector3& operator-=(const Vector3& rhs) {
			r -= rhs.r;
			g -= rhs.g;
			b -= rhs.b;
			return *this;
		}

		// Multiplication (element-wise)
		Vector3 operator*(const Vector3& rhs) const {
			return Vector3(r * rhs.r, g * rhs.g, b * rhs.b);
		}

		// Division (element-wise)
		Vector3 operator/(const Vector3& rhs) const {
			return Vector3(r / rhs.r, g / rhs.g, b / rhs.b);
		}

		// Length between this and another vector
		float length(const Vector3& other) const {
			float dx = static_cast<float>(r - other.r);
			float dy = static_cast<float>(g - other.g);
			float dz = static_cast<float>(b - other.b);
			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}
	};

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}