#pragma once
#include "Player.h"
#include "Rocket.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Math/Math.h"
#include "Core/Time.h"
#include "Framework/Scene.h"
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

    m_transform.position.x = swaws::math::wrap((float)m_transform.position.x, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    m_transform.position.y = swaws::math::wrap((float)m_transform.position.y, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    // Check for Rocket Fire
    if (swaws::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_E) || swaws::GetEngine().GetInputSystem().GetMouseButtonPressed(swaws::InputSystem::MouseButton::Left))
    {
        // Spawn rocket in direction facing
        std::unique_ptr<Rocket> rocket = std::make_unique<Rocket>();
        rocket->GetTransform().position = m_transform.position;
        rocket->GetTransform().rotation = m_transform.rotation;
        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
}
