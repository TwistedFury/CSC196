#pragma once
#include "Framework/Game.h"

class SpaceGame : public swaws::Game
{
public:
	SpaceGame() = default;

	bool Initialize() override;
	void Update() override;
	void Shutdown() override;
	void Draw() override;
private:

};