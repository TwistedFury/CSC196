#pragma once

#include <cmath>

namespace swaws {
	template <typename T>
	struct Vector2
	{
		T x, y;

		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		// Operators added by GitHub Copilot

		// Addition
		Vector2 operator+(const Vector2& rhs) const {
			return Vector2(x + rhs.x, y + rhs.y);
		}
		Vector2& operator+=(const Vector2& rhs) {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		// Subtraction
		Vector2 operator-(const Vector2& rhs) const {
			return Vector2(x - rhs.x, y - rhs.y);
		}
		Vector2& operator-=(const Vector2& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		// Multiplication (element-wise)
		Vector2 operator*(const Vector2& rhs) const {
			return Vector2(x * rhs.x, y * rhs.y);
		}

		// Division (element-wise)
		Vector2 operator/(const Vector2& rhs) const {
			return Vector2(x / rhs.x, y / rhs.y);
		}

		// Length between this and another vector
		float length(const Vector2& other) const {
			float dx = static_cast<float>(x - other.x);
			float dy = static_cast<float>(y - other.y);
			return std::sqrt(dx * dx + dy * dy);
		}
	};

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}