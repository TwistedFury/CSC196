#pragma once
#include "Player.h"

#include "Engine.h"
#include "Input/InputSystem.h"
#include "Core/Time.h"

#include "SDL3/SDL.h"

void Player::Update(float dt)
{
    // rotation
    float rotate = 0;
    if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    m_transform.rotation += (rotate * rotationRate) * dt;

    // thrust
    float thrust = 0;
    if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(m_transform.rotation)) * thrust * speed;
    velocity += force * dt;

    Actor::Update(dt);

    //if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
    //if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_S)) direction.y = +1;
    //if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
    //if (swaws::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) direction.x = +1;

    //if (direction.LengthSqr() > 0)
    //{
    //    direction = direction.Normalized();
    //    m_transform.position += (direction * speed) * dt;
    //}
}
