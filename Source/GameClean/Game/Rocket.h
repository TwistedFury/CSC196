#pragma once

#include "Framework/Actor.h" 

class Rocket : public swaws::Actor
{
public:
	Rocket() = default;

	Rocket(const swaws::Transform& transform, std::shared_ptr<swaws::Model> model) :
		swaws::Actor{ transform, model } { }

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

};