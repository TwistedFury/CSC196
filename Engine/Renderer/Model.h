#pragma once

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include <vector>

namespace swaws
{
	class Model
	{
	public:
		Model() = default;

		Model(const std::vector<vec2>& verts, const vec3& color) : m_verts{ verts }, color{ color } {}

		void Draw(class Renderer& renderer, const vec2& position, float rotation, float scale);
	private:
		std::vector<vec2> m_verts;
		vec3 color{1, 1, 1};
	};
}
