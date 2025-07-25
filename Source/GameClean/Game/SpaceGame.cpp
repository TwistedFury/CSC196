#pragma once

#include "SpaceGame.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Core/Time.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Player.h"

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

    std::shared_ptr<swaws::Model> model = std::make_shared < swaws::Model>(player_points, swaws::vec3{ 0.0f, 1.0f, 0.8f });

    swaws::Transform transform(swaws::vec2{ swaws::GetEngine().GetRenderer().GetWindowWidth() * 0.5f, swaws::GetEngine().GetRenderer().GetWindowHeight() * 0.5f}, 0, 5);
    std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
    scene->AddActor(std::move(player));
    
    /*for (int i = 0; i < 10; i++)
    {
        swaws::Transform transform(swaws::vec2{ swaws::random::GetRandomFloat() * 1280, swaws::random::GetRandomFloat() * 1020 });
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        scene->AddActor(std::move(player));
    }
    */
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
