#pragma once

#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"

namespace swaws
{

	void Scene::Update(float dt)
	{
		for (auto& act : m_actors)
		{
			act->Update(dt);
		}
	}


	void Scene::Draw(Renderer& renderer)
	{
		for (auto& act : m_actors)
		{
			act->Draw(renderer);
		}
	}


	void Scene::AddActor(std::unique_ptr<Actor> act)
	{
		m_actors.push_back(std::move(act));
	}

}