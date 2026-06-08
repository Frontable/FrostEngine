#pragma once
#include <cstdlib>
#include "FrostMath.h"
#include "ECS/Components.h"

// ======================================================
// Add new sprites here
// ======================================================
enum class SpriteID
{
    PLAYER,
    PLAYER_BULLET,
    PLAYER_THRUSTER,


    //ASSTERIOID
    ASTEROID_LARGE,
    //MEDIUM
    ASTEROID_MEDIUM_TOP_LEFT,
    ASTEROID_MEDIUM_TOP_RIGHT,
    ASTEROID_MEDIUM_BOTTOM_LEFT,
    ASTEROID_MEDIUM_BOTTOM_RIGHT,
    //SMOL TOP LEFT
    ASTEROID_SMALL_TOP_LEFT_TOP_LEFT,
    ASTEROID_SMALL_TOP_LEFT_TOP_RIGHT,
    ASTEROID_SMALL_TOP_LEFT_BOTTOM_LEFT,
    ASTEROID_SMALL_TOP_LEFT_BOTTOM_RIGHT,
    //SMOL TOP RIGHT
    ASTEROID_SMALL_TOP_RIGHT_TOP_LEFT,
    ASTEROID_SMALL_TOP_RIGHT_TOP_RIGHT,
    ASTEROID_SMALL_TOP_RIGHT_BOTTOM_LEFT,
    ASTEROID_SMALL_TOP_RIGHT_BOTTOM_RIGHT,
    //SMOL BOTTOM LEFT
    ASTEROID_SMALL_BOTTOM_LEFT_TOP_LEFT,
    ASTEROID_SMALL_BOTTOM_LEFT_TOP_RIGHT,
    ASTEROID_SMALL_BOTTOM_LEFT_BOTTOM_LEFT,
    ASTEROID_SMALL_BOTTOM_LEFT_BOTTOM_RIGHT,
    //SMOL BOTTOM RIGHT
    ASTEROID_SMALL_BOTTOM_RIGHT_TOP_LEFT,
    ASTEROID_SMALL_BOTTOM_RIGHT_TOP_RIGHT,
    ASTEROID_SMALL_BOTTOM_RIGHT_BOTTOM_LEFT,
    ASTEROID_SMALL_BOTTOM_RIGHT_BOTTOM_RIGHT,
    //ASTEROIDS END


    COUNT
};

// ======================================================
// Atlas dimensions
// ======================================================
constexpr float ATLAS_WIDTH = 250.0f;
constexpr float ATLAS_HEIGHT = 250.0f;

// ======================================================
// Sprite registry
// ======================================================
inline Sprite GetSprite(SpriteID id)
{
    switch (id)
    {
    case SpriteID::PLAYER:
        return { {0.0f,   0.0f},  {32.0f, 32.0f} };
    case SpriteID::PLAYER_BULLET:
        return { {69.0f,   76.0f},  {72.0f,  78.0f} };
    case SpriteID::PLAYER_THRUSTER:
        return { {69.0f, 14.0f}, {18.0f, 14.0f} };

    //ASSTEROIDS
    case SpriteID::ASTEROID_LARGE:
        return { {64.0f,  189.0f}, {60.0f, 60.0f} };
    //ROIDS MEDIUM
    case SpriteID::ASTEROID_MEDIUM_TOP_LEFT:
        return { {130.0f, 190.0f}, {27.0f, 29.0f} };
    case SpriteID::ASTEROID_MEDIUM_TOP_RIGHT:
        return { {157.0f, 190.0f}, {26.0f, 26.0f} };
    case SpriteID::ASTEROID_MEDIUM_BOTTOM_LEFT:
        return { {130.0f, 220.0f}, {26.0f, 26.0f} };
    case SpriteID::ASTEROID_MEDIUM_BOTTOM_RIGHT:
        return { {157.0f, 220.0f}, {27.0f, 29.0f} };
    //SMALL ROIDS TOP LEFT
    case SpriteID::ASTEROID_SMALL_TOP_LEFT_TOP_LEFT:
        return { {194.0f, 192.0f}, {9.0f, 10.0f} };
    case SpriteID::ASTEROID_SMALL_TOP_LEFT_TOP_RIGHT:
        return { {204.0f, 192.0f}, {13.0f, 10.0f} };
    case SpriteID::ASTEROID_SMALL_TOP_LEFT_BOTTOM_LEFT:
        return { {194.0f, 204.0f}, {9.0f, 12.0f} };
    case SpriteID::ASTEROID_SMALL_TOP_LEFT_BOTTOM_RIGHT:
        return { {204.0f, 204.0f}, {14.0f, 14.0f} };
        //SMALL ROIDS TOP RIGHT
    case SpriteID::ASTEROID_SMALL_TOP_RIGHT_TOP_LEFT:
        return { {221.0f, 192.0f}, {12.0f, 10.0f} };
    case SpriteID::ASTEROID_SMALL_TOP_RIGHT_TOP_RIGHT:
        return { {235.0f, 195.0f}, {10.0f, 7.0f} };
    case SpriteID::ASTEROID_SMALL_TOP_RIGHT_BOTTOM_LEFT:
        return { {220.0f, 204.0f}, {14.0f, 13.0f} };
    case SpriteID::ASTEROID_SMALL_TOP_RIGHT_BOTTOM_RIGHT:
        return { {235.0f, 204.0f}, {10.0f, 12.0f} };
        //SMALL ROIDS BOTTOM LEFT
    case SpriteID::ASTEROID_SMALL_BOTTOM_LEFT_TOP_LEFT:
        return { {192.0f, 220.0f}, {10.0f, 14.0f} };
    case SpriteID::ASTEROID_SMALL_BOTTOM_LEFT_TOP_RIGHT:
        return { {204.0f, 220.0f}, {12.0f, 14.0f} };
    case SpriteID::ASTEROID_SMALL_BOTTOM_LEFT_BOTTOM_LEFT:
        return { {196.0f, 235.0f}, {6.0f, 7.0f} };
    case SpriteID::ASTEROID_SMALL_BOTTOM_LEFT_BOTTOM_RIGHT:
        return { {204.0f, 235.0f}, {14.0f, 10.0f} };
        //SMALL ROIDS BOTTOM RIGHT
    case SpriteID::ASTEROID_SMALL_BOTTOM_RIGHT_TOP_LEFT:
        return { {220.0f, 220.0f}, {13.0f, 14.0f} };
    case SpriteID::ASTEROID_SMALL_BOTTOM_RIGHT_TOP_RIGHT:
        return { {235.0f, 221.0f}, {10.0f, 13.0f} };
    case SpriteID::ASTEROID_SMALL_BOTTOM_RIGHT_BOTTOM_LEFT:
        return { {210.0f, 235.0f}, {13.0f, 13.0f} };
    case SpriteID::ASTEROID_SMALL_BOTTOM_RIGHT_BOTTOM_RIGHT:
        return { {235.0f, 235.0f}, {10.0f, 10.0f} };
    //ROIDS END

    

    default:
        return { {0.0f, 0.0f}, {0.0f, 0.0f} };
    }
}

inline Sprite GetRandomMediumAsteroid()
{
    int r = rand() % 4;
    switch (r)
    {
    case 0: return GetSprite(SpriteID::ASTEROID_MEDIUM_TOP_LEFT);
    case 1: return GetSprite(SpriteID::ASTEROID_MEDIUM_TOP_RIGHT);
    case 2: return GetSprite(SpriteID::ASTEROID_MEDIUM_BOTTOM_LEFT);
    default: return GetSprite(SpriteID::ASTEROID_MEDIUM_BOTTOM_RIGHT);
    }
}

inline Sprite GetRandomSmallAsteroid()
{
    int r = rand() % 16;
    switch (r)
    {
    case 0:  return GetSprite(SpriteID::ASTEROID_SMALL_TOP_LEFT_TOP_LEFT);
    case 1:  return GetSprite(SpriteID::ASTEROID_SMALL_TOP_LEFT_TOP_RIGHT);
    case 2:  return GetSprite(SpriteID::ASTEROID_SMALL_TOP_LEFT_BOTTOM_LEFT);
    case 3:  return GetSprite(SpriteID::ASTEROID_SMALL_TOP_LEFT_BOTTOM_RIGHT);
    case 4:  return GetSprite(SpriteID::ASTEROID_SMALL_TOP_RIGHT_TOP_LEFT);
    case 5:  return GetSprite(SpriteID::ASTEROID_SMALL_TOP_RIGHT_TOP_RIGHT);
    case 6:  return GetSprite(SpriteID::ASTEROID_SMALL_TOP_RIGHT_BOTTOM_LEFT);
    case 7:  return GetSprite(SpriteID::ASTEROID_SMALL_TOP_RIGHT_BOTTOM_RIGHT);
    case 8:  return GetSprite(SpriteID::ASTEROID_SMALL_BOTTOM_LEFT_TOP_LEFT);
    case 9:  return GetSprite(SpriteID::ASTEROID_SMALL_BOTTOM_LEFT_TOP_RIGHT);
    case 10: return GetSprite(SpriteID::ASTEROID_SMALL_BOTTOM_LEFT_BOTTOM_LEFT);
    case 11: return GetSprite(SpriteID::ASTEROID_SMALL_BOTTOM_LEFT_BOTTOM_RIGHT);
    case 12: return GetSprite(SpriteID::ASTEROID_SMALL_BOTTOM_RIGHT_TOP_LEFT);
    case 13: return GetSprite(SpriteID::ASTEROID_SMALL_BOTTOM_RIGHT_TOP_RIGHT);
    case 14: return GetSprite(SpriteID::ASTEROID_SMALL_BOTTOM_RIGHT_BOTTOM_LEFT);
    default: return GetSprite(SpriteID::ASTEROID_SMALL_BOTTOM_RIGHT_BOTTOM_RIGHT);
    }
}