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
		m_transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	/// <summary>
	/// Draws the actor using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actor.</param>
	void Actor::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}
