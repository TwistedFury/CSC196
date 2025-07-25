#pragma once

#include "Framework/Actor.h" 

class Player : public swaws::Actor
{
public:
	float speed = 200;
	float rotationRate = 180;
public:
	Player() = default;
	
	Player(const swaws::Transform& transform, std::shared_ptr<swaws::Model> model) :
		swaws::Actor{ transform, model } { this->damping = 0.2f; }

	void Update(float dt) override;
	
private:
};