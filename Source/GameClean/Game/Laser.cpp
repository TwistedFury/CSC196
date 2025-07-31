#pragma once

#include "Laser.h"
#include "Engine.h"
#include "EngineInc.h"
#include "Player.h"

void Laser::Update(float dt)
{
    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(transform.rotation)) * speed;
    velocity = force;

    lifespan -= dt;
    if (lifespan <= 0) destroyed = true;
}

void Laser::Draw(swaws::Renderer& renderer)
{
    // Get Player Reference
    Player* player = dynamic_cast<Player*>(scene->GetActorByName("player"));
    // Create a unit vector pointing right, rotate it by the player's rotation, and scale by laser length
    swaws::vec2 direction = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(player->transform.rotation));
    float laserLength = 1000.0f; // Set your desired laser length
    swaws::vec2 endPoint = player->transform.position + direction * laserLength;

    renderer.SetColor(1.0f, 0.0f, 0.0f);
    renderer.DrawLine(transform.position.x, transform.position.y, endPoint.x, endPoint.y);
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
