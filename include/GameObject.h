




#include "Sprite.h"
#include "SpriteRenderer.h"

struct GameObject
{
    unsigned int ID;

    //components || To be modified to an ECS

    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 vel, SpriteID sprite, int frames)
    :pos(pos), size(size), velocity(vel)
    {
        m_sprite = getSprite(sprite);
        m_animation.frameCount = frames;
        m_animation.frameDuration = 0.5f;
    }

    inline void Update(float dt)
    {

        m_animation.Update(dt);

    }

    inline void Draw()
    {
        SpriteRenderer::GetInstance()->Draw(ATLAS, pos, size, 0, glm::vec3(1), SHROOM_SPRITE, m_animation.currentFrame);
    }

    glm::vec2 pos, size, velocity;
    Sprite m_sprite;
    Animation m_animation;

};