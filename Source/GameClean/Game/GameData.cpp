#pragma once
#include "GameData.h"

namespace GameData
{
    std::vector<swaws::vec2> playerPoints{
    { 6, 0 },
    { -6, -4 },
    { -4, 0 },
    { -6, 4 },
    { 6, 0 }
    };

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
}