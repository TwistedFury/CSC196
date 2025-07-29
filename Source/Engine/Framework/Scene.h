#pragma once

#include <vector>
#include <string>
#include <memory>

namespace swaws
{
	class Scene
	{
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<class Actor> act);

		std::vector<std::unique_ptr<class Actor>>& GetActors() { return m_actors; }

		Actor* GetActorByName(const std::string& name);

	private:
		std::vector<std::unique_ptr<class Actor>> m_actors;
	};
}