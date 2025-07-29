#pragma once

#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "EngineInc.h"

#include <vector>

bool SpaceGame::Initialize()
{
    scene = std::make_unique<swaws::Scene>();

    std::vector<swaws::vec2> player_points{
        { 6, 0 },
        { -6, -4 },
        { -4, 0 },
        { -6, 4 },
        { 6, 0 }
    };

    std::shared_ptr<swaws::Model> model = std::make_shared <swaws::Model>(player_points, swaws::vec3{ 0.0f, 1.0f, 0.8f });

    swaws::Transform transform(swaws::vec2{ swaws::GetEngine().GetRenderer().GetWindowWidth() * 0.5f, swaws::GetEngine().GetRenderer().GetWindowHeight() * 0.5f}, 0, 5);
    std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
    player->damping = 0.5f; // Set Damping for player
    player->speed = 1500; // Set player Speed
    player->rotationRate = 180; // Set Rotation Rate

    // Give player name
    player->name = "player";

    scene->AddActor(std::move(player));
    
    std::vector<swaws::vec2> enemyPoints{
        { -8, 0 },
        { -5, -1 },
        { -2, -2 },
        { 2, -2 },
        { 5, -1 },
        { 8, 0 },
        { 3, 2 },
        { -3, 2 },
        { -8, 0 }
    };

    std::shared_ptr<swaws::Model> enemyModel = std::make_shared <swaws::Model>(enemyPoints, swaws::vec3{ 1.0f, 1.0f, 0.0f });
    for (int i = 0; i < 1000; i++) {
        swaws::Transform transform{ swaws::vec2{ swaws::random::GetRandomFloat() * swaws::GetEngine().GetRenderer().GetWindowWidth(), swaws::random::GetRandomFloat() * swaws::GetEngine().GetRenderer().GetWindowHeight()}, 0, 5};
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
        enemy->damping = 100;
        enemy->speed = (swaws::random::GetRandomFloat() * 10000) + 700;
        if (enemy->speed > 1500) enemy->speed = 1500;
        scene->AddActor(std::move(enemy));
    }

    return true;
}

void SpaceGame::Update()
{
    scene->Update(swaws::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Shutdown()
{
    //
}

void SpaceGame::Draw()
{
    for (auto& act : scene->GetActors())
    {
        act->Draw(swaws::GetEngine().GetRenderer());
    }
}
