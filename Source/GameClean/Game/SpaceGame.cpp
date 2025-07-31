#pragma once

#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"
#include "EngineInc.h"

#include <vector>

bool SpaceGame::Initialize()
{
    scene = std::make_unique<swaws::Scene>(this);

    m_titleFont = std::make_shared<swaws::Font>();
    m_titleFont->Load("font.ttf", 128);

    m_uiFont = std::make_shared<swaws::Font>();
    m_uiFont->Load("font.ttf", 48);

    m_titleText = std::make_unique<swaws::Text>(m_titleFont);
    m_scoreText = std::make_unique<swaws::Text>(m_uiFont);
    m_livesText = std::make_unique<swaws::Text>(m_uiFont);

    return true;
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;
    case SpaceGame::GameState::Title:
        if (swaws::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) m_gameState = GameState::StartGame;
        break;
    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::StartRound:
    {
        std::shared_ptr<swaws::Model> model = std::make_shared <swaws::Model>(GameData::playerPoints, swaws::vec3{ 0.0f, 1.0f, 0.8f });
        swaws::Transform transform(swaws::vec2{ swaws::GetEngine().GetRenderer().GetWindowWidth() * 0.5f, swaws::GetEngine().GetRenderer().GetWindowHeight() * 0.5f }, 0, 5);
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        player->damping = 0.5f; // Set Damping for player
        player->speed = 1500; // Set player Speed
        player->rotationRate = 180; // Set Rotation Rate

        // Give player name
        player->tag = "player";
        player->name = "player";
        scene->AddActor(std::move(player));
        m_gameState = GameState::Game;
    }
        break;
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0)
        {
            m_enemySpawnTimer = 4;
            std::shared_ptr<swaws::Model> enemyModel = std::make_shared <swaws::Model>(GameData::enemyPoints, swaws::vec3{ 1.0f, 1.0f, 0.0f });
            swaws::Transform transform{ swaws::vec2{ swaws::random::getReal<float>() * swaws::GetEngine().GetRenderer().GetWindowWidth(), swaws::random::getReal<float>() * swaws::GetEngine().GetRenderer().GetWindowHeight()}, 0, 5 };
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
            enemy->damping = 0.2f;
            enemy->speed = 0;//(swaws::random::GetRandomFloat() * 10000) + 700;
            if (enemy->speed > 1500) enemy->speed = 1500;
            enemy->tag = "enemy";
            scene->AddActor(std::move(enemy));
        }
        break;
    case SpaceGame::GameState::PlayerDead:
        break;
    case SpaceGame::GameState::GameOver:
        break;
    default:
        break;
    }

    scene->Update(swaws::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Shutdown()
{
    //
}

void SpaceGame::Draw()
{
    swaws::GetEngine().GetRenderer().Clear();
    scene->Draw(swaws::GetEngine().GetRenderer());
    swaws::GetEngine().GetRenderer().Present();
}
