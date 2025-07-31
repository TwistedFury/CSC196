#pragma once

namespace swaws
{
	class ParticleSystem
	{
	public:
		ParticleSystem() = default;

		ParticleSystem(int poolSize) : poolSize{ poolSize } {}

	private:
		int poolSize = 10;

	};
}