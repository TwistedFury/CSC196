#pragma once
#include "EngineInc.h"
#include "Enemy.h"
#include "Player.h"
#include "GameData.h"
#include "Rocket.h"

void Enemy::Update(float dt)
{
    bool playerSeen = false;
    Player* player = scene->GetActorByName<Player>("player");
    if (player)
    {
        swaws::vec2 direction{ 0, 0 }; 
        direction = player->GetTransform().position - transform.position;
        
        direction = direction.Normalized();
        swaws::vec2 forward = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(transform.rotation));

        float angle = swaws::math::RadToDeg(swaws::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;

        if (playerSeen)
        {
            float angle = swaws::vec2::SignedAngleBetween(direction, forward);
            angle = swaws::math::sign(angle);
            transform.rotation += swaws::math::RadToDeg(angle * dt);
        }
    }

    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(transform.rotation)) * speed;
    velocity += force * dt;

    if (velocity.x > maxSpeed || force.x > maxSpeed) velocity = { maxSpeed, velocity.y };
    if (velocity.y > maxSpeed || force.y > maxSpeed) velocity = { velocity.x, maxSpeed };

    transform.position.x = swaws::math::wrap((float)transform.position.x, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    transform.position.y = swaws::math::wrap((float)transform.position.y, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    std::shared_ptr<swaws::Model> model;
    std::unique_ptr<Rocket> rocket;    
    swaws::Transform transform(this->transform.position, this->transform.rotation, 5);

    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen)
    {
        fireTimer = fireTime;
        // Spawn rocket in direction facing
        model = std::make_shared <swaws::Model>(GameData::rocketPoints, swaws::vec3{ 0.0f, 1.0f, 0.0f });
        rocket = std::make_unique<Rocket>(transform, model);
        rocket->speed = 200; // Set Speed
        rocket->lifespan = 1;
        rocket->tag = "enemy"; // Set Tag
        rocket->name = "rocket";

        scene->AddActor(std::move(rocket));
    }
    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
    if (tag != other->tag)
    {
        destroyed = true;
        scene->GetGame()->AddPoints(100);
        // Explosion Particles
        for (int i = 0; i < 100; i++)
        {
            swaws::Particle particle;
            particle.position = transform.position;
            particle.velocity = swaws::vec2{ swaws::random::getReal(-200.0f, 200.0f), swaws::random::getReal(-200.0f, 200.0f) };
            particle.color = swaws::vec3{ 1, 1, 1 };
            particle.lifespan = 2;

            swaws::GetEngine().GetPS().AddParticle(particle);
        }
    }
}
