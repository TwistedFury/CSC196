#pragma once
#include "EngineInc.h"
#include "Enemy.h"
#include "Player.h"

void Enemy::Update(float dt)
{
    Player* player = scene->GetActorByName<Player>("player");
    if (player)
    {
        swaws::vec2 direction{ 0, 0 }; 
        direction = player->GetTransform().position - m_transform.position;
        direction = direction.Normalized();
        m_transform.rotation = swaws::math::RadToDeg(direction.Angle());
    }

    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(m_transform.rotation)) * speed;
    velocity += force * dt;

    m_transform.position.x = swaws::math::wrap((float)m_transform.position.x, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    m_transform.position.y = swaws::math::wrap((float)m_transform.position.y, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
    if (tag != other->tag)
    {
        destroyed = true;
        scene->GetGame()->AddPoints(100);
    }
}
