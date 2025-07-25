#pragma once
#include <cstdlib>

namespace swaws {
	namespace random {
		/// <summary>
		/// Generates a random number.
		/// </summary>
		/// <returns>A pseudo-random integer value</returns>
		inline int GetRandom() { return rand(); }

		/// <summary>
		/// Generates a random number in the range [0, max).
		/// </summary>
		/// <param name="max">The upper bound (exclusive) for the random integer</param>
		/// <returns>A random integer greater than or equal to 0 and less than the max</returns>
		inline int GetRandom(int max) { return rand() % max; }

		/// <summary>
		/// Generates a random integer within a specified inclusive range.
		/// </summary>
		/// <param name="min">The lower bound of the range (inclusive).</param>
		/// <param name="max">The upper bound of the range (inclusive).</param>
		/// <returns>A random integer value between min and max, inclusive.</returns>
		inline int GetRandom(int min, int max) { return min + GetRandom(max - min + 1); }

		/// <summary>
		/// Generates a random floating-point number between 0.0 and 1.0.
		/// </summary>
		/// <returns>A random float value in the range [0.0, 1.0].</returns>
		inline float GetRandomFloat() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); }
	}
}