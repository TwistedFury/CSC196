#pragma once

#include "Framework/Actor.h" 

class Player : public swaws::Actor
{
public:
	float speed = 200;
	float rotationRate = 180;
	float damping = 0.5f;
public:
	Player() = default;
	
	Player(const swaws::Transform& transform, std::shared_ptr<swaws::Model> model) :
		swaws::Actor{ transform, model } { }

	void Update(float dt) override;
	
private:

};