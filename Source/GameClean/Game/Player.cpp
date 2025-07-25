#pragma once
#include "Player.h"

#include "Engine.h"
#include "Input/InputSystem.h"
#include "Core/Time.h"

#include "SDL3/SDL.h"

void Player::Update(float dt)
{
    swaws::vec2 direction{ 0, 0 };
    if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
    if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_S)) direction.y = +1;
    if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
    if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) direction.x = +1;

    if (direction.LengthSqr() > 0)
    {
        direction = direction.Normalized();
        m_transform.position += (direction * speed) * dt;
    }
}
