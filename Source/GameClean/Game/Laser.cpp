#pragma once

#include "Laser.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Math/Vector2.h"

void Laser::Update(float dt)
{
    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(transform.rotation)) * speed;
    velocity = force;

    transform.position.x = swaws::math::wrap((float)transform.position.x, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    transform.position.y = swaws::math::wrap((float)transform.position.y, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());
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
