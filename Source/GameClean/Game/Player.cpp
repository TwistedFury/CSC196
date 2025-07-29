#pragma once
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"
#include "EngineInc.h"

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
    if ((swaws::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_E) || swaws::GetEngine().GetInputSystem().GetMouseButtonPressed(swaws::InputSystem::MouseButton::Left)) && fireTimer <= 0)
    {
        fireTimer = fireTime;
        // Spawn rocket in direction facing
        std::shared_ptr<swaws::Model> model = std::make_shared <swaws::Model>(GameData::rocketPoints, swaws::vec3{ 0.0f, 1.0f, 0.8f });
        swaws::Transform transform(this->m_transform.position, swaws::math::DegToRad(this->m_transform.rotation), 5);
        std::unique_ptr<Rocket> rocket = std::make_unique<Rocket>(transform, model);
        rocket->speed = 750; // Set Speed
        rocket->lifespan = 1.5f;
        rocket->tag = "player"; // Set Tag
        rocket->name = "rocket";

        scene->AddActor(std::move(rocket));
    }
    fireTimer--;
    Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    if (tag != other->tag)
    {
        destroyed = true;
    }
}
