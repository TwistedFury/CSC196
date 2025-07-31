#pragma once
#include "Actor.h"
#include "../Renderer/Model.h"

namespace swaws
{
	/// <summary>
	/// Updates the actor's position and velocity based on the elapsed time and damping.
	/// </summary>
	/// <param name="dt">The elapsed time since the last update, in seconds.</param>
	void Actor::Update(float dt)
	{
		if (destroyed) return;

		if (lifespan != 0)
		{
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		// Larger effect on damping speed with std::exp
		m_transform.position += velocity * dt;
		velocity *= std::exp(-damping * dt);
	}

	/// <summary>
	/// Draws the actor using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actor.</param>
	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;
		m_model->Draw(renderer, m_transform);
	}
	float Actor::GetRadius()
	{
		return (m_model) ? m_model->GetRadius() * m_transform.scale : 0;
	}
}
