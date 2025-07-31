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
    m_titleFont->Load("8bitOperatorPlus8-Regular.ttf", 64);

    m_uiFont = std::make_shared<swaws::Font>();
    m_uiFont->Load("8bitOperatorPlus8-Regular.ttf", 48);

    m_titleText = std::make_unique<swaws::Text>(m_titleFont);
    m_scoreText = std::make_unique<swaws::Text>(m_uiFont);
    m_livesText = std::make_unique<swaws::Text>(m_uiFont);

    // Initialize Laser Points
    GameData::laserPoints = std::vector<swaws::vec2>{
    { 0, 0 },
    { (float)swaws::GetEngine().GetRenderer().GetWindowWidth(), 0}
    };

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
        if (swaws::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) m_gameState = GameState::StartGame;
        break;
    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::StartRound:
    {
        scene->RemoveAllActors();
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
            SpawnEnemy();
        }
        break;
    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_lives--;
            if (m_lives == 0)
            {
                m_stateTimer = 3;
                m_gameState = GameState::GameOver;
            }
            else m_gameState = GameState::StartRound;
        }
        break;
    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) m_gameState = GameState::Title;
        break;
    default:
        break;
    }

    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) swaws::GetEngine().GetTime().SetTimeScale(0.2f); // SUPER HOT SUPER HOT SUPER HOT
    else swaws::GetEngine().GetTime().SetTimeScale(1.0f);
    scene->Update(swaws::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Shutdown()
{
    //
}

void SpaceGame::Draw(swaws::Renderer& renderer)
{
    //swaws::GetEngine().GetRenderer().Clear();
    if (m_gameState == GameState::Title)
    {
        m_titleText->Create(renderer, "OUI WUZ SPACE", swaws::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 400);
    }
    if (m_gameState == GameState::GameOver)
    {
        m_titleText->Create(renderer, "GAME OVER", swaws::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 400);
    }

    // Score and "Other Stuff"
    m_scoreText->Create(renderer, "SCORE    " + std::to_string(m_score), {1, 1, 1});
    m_scoreText->Draw(renderer, 20, 20);

    m_livesText->Create(renderer, "LIVES    " + std::to_string(m_lives), {1, 1, 1});
    m_livesText->Draw(renderer, (float)renderer.GetWindowWidth() - 300.0f, 20);

    scene->Draw(renderer);
    //swaws::GetEngine().GetRenderer().Present();
    swaws::GetEngine().GetPS().Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2;
}

void SpaceGame::SpawnEnemy()
{
    std::shared_ptr<swaws::Model> enemyModel = std::make_shared <swaws::Model>(GameData::enemyPoints, swaws::vec3{ 1.0f, 1.0f, 0.0f });
    
    Player* player = scene->GetActorByName<Player>("player");
    if (player)
    {
        // Spawn @ Random Position away from Player
        swaws::vec2 position = player->transform.position + swaws::random::onUnitCircle() * swaws::random::getReal(200.0f, 500.0f);
        swaws::Transform transform{ position, swaws::random::getReal(0.0f, 360.0f), 5};
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);

        enemy->damping = 0.7f;
        enemy->speed = (swaws::random::getReal() * 200) + 100;
        enemy->tag = "enemy";
        enemy->fireTime = 2;
        enemy->fireTimer = 5;
        scene->AddActor(std::move(enemy));
    }
}
