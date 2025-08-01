#pragma once
#include "EngineInc.h"

class UIModel : public swaws::Actor
{
public:
	// Inherited via Actor
	void OnCollision(Actor* other) override
	{
	}

	UIModel(const swaws::Transform& transform, std::shared_ptr<swaws::Model> model) :
		swaws::Actor{ transform, model } {}
};