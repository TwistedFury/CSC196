#pragma once
#include "Framework/Actor.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include <iostream>

class Laser : public swaws::Actor
{
public:
	bool pierce{ false };

public:
	Laser() = default;

	Laser(const swaws::Transform& transform, std::shared_ptr<swaws::Model> model) :
		swaws::Actor{ transform, model } { }

	void Update(float dt) override;

	void Draw(swaws::Renderer& renderer) override;

	void OnCollision(Actor* other) override;

private:
};