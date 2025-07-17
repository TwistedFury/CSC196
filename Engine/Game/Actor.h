#pragma once

#include "../Math/Transform.h"
#include "../Renderer/Model.h"
#include <memory>

namespace swaws
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const Transform& transform, std::shared_ptr<Model> model) :
		m_transform{ transform }, m_model{ model } 
		{ }

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		Transform& GetTransform() { return m_transform; }

	private:
		Transform m_transform;
		std::shared_ptr<Model> m_model;
	};
}