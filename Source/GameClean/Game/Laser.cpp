#pragma once

#include "Laser.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Math/Vector2.h"

void Laser::Update(float dt)
{
    Draw(swaws::GetEngine().GetRenderer());
}

void Laser::OnCollision(Actor* other)
{
    if (pierce)
    {

    }
    else
    {

    }
}

void Laser::Draw(swaws::Renderer& renderer)
{
    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 rotatedDir = direction.Rotate(swaws::math::DegToRad(m_transform.rotation));
    // Draw straight line in direction until end of screen
    rotatedDir = rotatedDir.Normalized();

    int width = swaws::GetEngine().GetRenderer().GetWindowWidth();
    int height = swaws::GetEngine().GetRenderer().GetWindowHeight();

    // Find a large distance to "guarantee" it hits an edge
    float maxDistance = std::max(width, height) * 2.0f;

    // End point = position + direction * large distance
    swaws::vec2 end = m_transform.position + rotatedDir * maxDistance;

    swaws::GetEngine().GetRenderer().SetColor(1.0f, 0.0f, 0.0f);
    swaws::GetEngine().GetRenderer().DrawLine(m_transform.position.x, m_transform.position.y, end.x, end.y);
    swaws::GetEngine().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);

    swaws::Actor::Draw(renderer);
}
