#pragma once

#include "Game/Actor.h" 

class Player : public swaws::Actor
{
public:
	Player() = default;
	
	Player(const swaws::Transform& transform, std::shared_ptr<swaws::Model> model) :
		swaws::Actor{ transform, model } { }

	void Update(float dt) override;
	
private:

};