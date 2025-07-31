#pragma once
#include "EngineInc.h"
#include "Enemy.h"
#include "Player.h"

void Enemy::Update(float dt)
{
    bool playerSeen = false;
    Player* player = scene->GetActorByName<Player>("player");
    if (player)
    {
        swaws::vec2 direction{ 0, 0 }; 
        direction = player->GetTransform().position - m_transform.position;
        
        direction = direction.Normalized();
        swaws::vec2 forward = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(m_transform.rotation));

        float angle = swaws::math::RadToDeg(swaws::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;

        if (playerSeen)
        {
            float angle = swaws::vec2::SignedAngleBetween(direction, forward);
            angle = swaws::math::sign(angle);
            m_transform.rotation += swaws::math::RadToDeg(angle * dt);
        }
    }

    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(m_transform.rotation)) * speed;
    velocity += force * dt;

    m_transform.position.x = swaws::math::wrap((float)m_transform.position.x, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    m_transform.position.y = swaws::math::wrap((float)m_transform.position.y, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    // Check Fire
    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen)
    {
        fireTimer = fireTime;
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
            particle.velocity = swaws::vec2{ swaws::random::getReal(-200.0f, 200.0f), viper::random::getReal(-200.0f, 200.0f) };
            particle.color = swaws::vec3{ 1, 1, 1 };
            particle.lifespan = 2;

            swaws::GetEngine().GetPS().AddParticle(particle);
        }
    }
}
