




#pragma once
#include "glm/glm.hpp"


struct Sprite
{
    glm::vec2 offSet;
    glm::vec2 size;
    glm::vec2 subSize;
    int frameCount = 1;
};

enum Atlas
{
    ATLAS,

    ATLAS_COUNT
};

enum SpriteID
{
    PLAYER_SPRITE,
    ENEMY_SPRITE,
    SHROOM_SPRITE,
    TEST,
    BACKGROUND,

    SPRITES_COUNT
};

struct Animation {
    int currentFrame = 0;
    int frameCount = 1;
    float frameDuration = 0.15f; // seconds per frame
    float timer = 0.0f;
    bool loop = true;

    Animation(int frames = 1, float duration = 0.15f, bool looping = true)
        : frameCount(frames), frameDuration(duration), loop(looping) {}

    void Update(float dt) {
        if (frameCount <= 1) return;

        timer += dt;
        if (timer >= frameDuration) {
            timer -= frameDuration;
            currentFrame++;
            if (currentFrame >= frameCount) {
                currentFrame = loop ? 0 : frameCount - 1;
            }
        }
    }
};

//offset will be the location start location in the atlas
//The size is the start to finish of all frames if we have more than 1
//and subsize if the size of 1 frame

inline Sprite getSprite(SpriteID sprite)
{
    Sprite s = {};
    switch(sprite)
    {
        case PLAYER_SPRITE:
        {
            s.offSet = {0, 0};
            s.size = {32, 32};
            break;
        }
        case ENEMY_SPRITE:
        {
            s.offSet = {32, 0};
            s.size = {32, 32};
            break;
        }
        case SHROOM_SPRITE:
        {
            s.offSet = {0, 0};
            s.size = {64, 32};
            s.subSize = {32, 32};            
            s.frameCount = 2;
            break;
        }
        case TEST:
        {
            s.offSet = {256, 944};
            s.size   = {96, 48};
            s.subSize = {48, 48};
            s.frameCount = 2;
            break;
        }
        case BACKGROUND:
        {
            s.offSet = {0, 0};
            s.size   = {4, 600};
            s.subSize = {800, 600};
            s.frameCount = 1;
            break;
        }
    }

    return s;
}