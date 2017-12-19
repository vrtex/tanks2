#pragma once
#include "SFML/Graphics.hpp"

struct TankInfo
{
    int index;
    sf::Vector2f position;
    int rotation;
    int turretRotation;
    int lean;
};
