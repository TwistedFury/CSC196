#pragma once
#include "EngineInc.h"
#include "Enemy.h"

void Enemy::Update(float dt)
{
    Actor* player = scene->GetActorByName("player");
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
