





#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Shader.h"
#include "Texture2D.h"

#include "Sprite.h"


class SpriteRenderer
{
    public:
    

    void DrawSprite(Texture2D& tex, glm::vec2 pos, glm::vec2 size, float rotation);
    void DrawSpriteUV(Texture2D& texture, glm::vec2 position, glm::vec2 size,
                                float rotate, glm::vec3 color, SpriteID sprite, int frameIndex);
    
    //testing atlas selection
    void Draw(Atlas atlas, glm::vec2 position, glm::vec2 size,
                                float rotate, glm::vec3 color, SpriteID sprite, int frameIndex);
    
    static SpriteRenderer* GetInstance();
    void SetShader(Shader& shader);

    private:
    void initData();
    void initDataNoUV();
    unsigned int quadVAO, quadVBO; //Buffers used for when i want to render with UV's
    unsigned int VAO,VBO; //Buffers used when i dont want to render with UV's
    Shader& m_shader;
    static SpriteRenderer* m_renderer;
    SpriteRenderer();
    ~SpriteRenderer();

};
