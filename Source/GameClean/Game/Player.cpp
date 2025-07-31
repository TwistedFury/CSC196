#pragma once
#include "Player.h"
#include "Rocket.h"
#include "Laser.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "EngineInc.h"

void Player::Update(float dt)
{
    swaws::Particle particle;
    particle.position = transform.position;
    particle.velocity = swaws::vec2{ swaws::random::getReal(-200.0f, 200.0f), swaws::random::getReal(-200.0f, 200.0f) };
    particle.color = { 1, 1, 1 };
    particle.lifespan = 2;
    swaws::GetEngine().GetPS().AddParticle(particle);

    // rotation
    float rotate = 0;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    transform.rotation += (rotate * rotationRate) * dt;

    // thrust
    float thrust = 0;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(transform.rotation)) * thrust * speed;
    velocity += force * dt;

    transform.position.x = swaws::math::wrap((float)transform.position.x, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    transform.position.y = swaws::math::wrap((float)transform.position.y, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    std::shared_ptr<swaws::Model> model;
    std::unique_ptr<Rocket> rocket;
    std::unique_ptr<Laser> laser;
    swaws::Transform transform(this->transform.position, this->transform.rotation, 5);
    
    // Check for Rocket Fire
    if ((swaws::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_E) || swaws::GetEngine().GetInput().GetMouseButtonPressed(swaws::InputSystem::MouseButton::Left)) && fireTimer <= 0)
    {
        fireTimer = fireTime;
        switch (weapon)
        {
        case Player::Weapon::Rocket:
            // Spawn rocket in direction facing
            model = std::make_shared <swaws::Model>(GameData::rocketPoints, swaws::vec3{ 0.0f, 1.0f, 0.8f });
            rocket = std::make_unique<Rocket>(transform, model);
            rocket->speed = 750; // Set Speed
            rocket->lifespan = 0.25f;
            rocket->tag = "player"; // Set Tag
            rocket->name = "rocket";

            scene->AddActor(std::move(rocket));
            break;
        case Player::Weapon::Laser:
            // Laser time BAYBEE
            model = std::make_shared<swaws::Model>(GameData::laserPoints, swaws::vec3{ 1.0f, 0.0f, 0.0f });
            laser = std::make_unique<Laser>(transform, model);
            laser->lifespan = 2.0f;
            laser->tag = "player";
            laser->name = "laser";

            scene->AddActor(std::move(laser));
            break;
        default:
            break;
        }
    }
    fireTimer--;
    Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    if (tag != other->tag)
    {
        destroyed = true;
        dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
    }
}
