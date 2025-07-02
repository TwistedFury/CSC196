#pragma once
#include <algorithm>

namespace swaws {
	namespace math {
		constexpr float pi = 3.14159265f;
		constexpr float twoPi = 2 * pi;
		constexpr float halfPi = pi / 2;

		/// <summary>
		/// Converts radians to degrees.
		/// </summary>
		/// <param name="rad">The angle in radians</param>
		/// <returns>The angle in degrees</returns>
		constexpr float RadToDeg(float rad) { return rad * (180 / pi); }

		/// <summary>
		/// Converts degrees to radians.
		/// </summary>
		/// <param name="deg">The angle in degrees</param>
		/// <returns>The angle in radians</returns>
		constexpr float DegToRad(float deg) { return deg * (pi / 180); }

		using std::min;
		using std::max;
		using std::clamp;
	}
}