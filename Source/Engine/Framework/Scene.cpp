#pragma once

#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"
#include "../Core/StringHelper.h"

namespace swaws
{
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt)
	{
		for (auto& act : m_actors)
		{
			act->Update(dt);
		}
	}

	/// <summary>
	/// Draws all actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(Renderer& renderer)
	{
		for (auto& act : m_actors)
		{
			act->Draw(renderer);
		}
	}

	/// <summary>
	/// Adds an actor to the scene.
	/// </summary>
	/// <param name="act">A unique pointer to the actor to be added.</param>
	void Scene::AddActor(std::unique_ptr<Actor> act)
	{
		act->scene = this;
		m_actors.push_back(std::move(act));
	}

	/// <summary>
	/// Retrieves an actor from the scene by its name.
	/// </summary>
	/// <param name="name">The name of the actor to search for.</param>
	/// <returns>A pointer to the actor with the specified name, or nullptr if no such actor exists.</returns>
	Actor* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (tolower(actor->name) == tolower(name)) return actor.get();
		}
		return nullptr;
	}

}