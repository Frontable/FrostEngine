

#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

SpriteRenderer *SpriteRenderer::m_renderer = nullptr;

SpriteRenderer *SpriteRenderer::GetInstance()
{
    if (m_renderer == nullptr)
    {
        m_renderer = new SpriteRenderer();
        return m_renderer;
    }

    return m_renderer;
}

void SpriteRenderer::SetShader(Shader &shader)
{
    m_shader = shader;
}

SpriteRenderer::SpriteRenderer()
    : m_shader(ResourceManager::GetShader("shader"))
{
    glGenVertexArrays(1, &quadVAO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &quadVBO);
    glGenBuffers(1, &VBO);
    initData();
    initDataNoUV();
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::DrawSprite(Texture2D &tex, glm::vec2 pos, glm::vec2 size, float rotate)
{
    m_shader.Use();
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(pos, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Use size, not texture dimensions
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f)); // Use the size parameter

    glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "model"), 1, GL_FALSE, &model[0][0]);
    tex.Use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0); // Good practice to unbind
}

void SpriteRenderer::DrawSpriteUV(Texture2D &texture, glm::vec2 position, glm::vec2 size,
                                  float rotate, glm::vec3 color, SpriteID sprite, int frameIndex)
{
    m_shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "model"), 1, GL_FALSE, &model[0][0]);

    Sprite s = getSprite(sprite);

    // Calculate UVs for the current frame
    glm::vec2 frameOffset = s.offSet + glm::vec2(frameIndex * s.subSize.x, 0);
    glm::vec2 uvStart(frameOffset.x / texture.m_width, frameOffset.y / texture.m_height);
    glm::vec2 uvEnd((frameOffset.x + s.subSize.x) / texture.m_width,
                    (frameOffset.y + s.subSize.y) / texture.m_height);

    float vertices[]{
        // Pos     //UV
        0.0f, 1.0f, uvStart.x, uvStart.y,
        1.0f, 0.0f, uvEnd.x, uvEnd.y,
        0.0f, 0.0f, uvStart.x, uvEnd.y,

        0.0f, 1.0f, uvStart.x, uvStart.y,
        1.0f, 1.0f, uvEnd.x, uvStart.y,
        1.0f, 0.0f, uvEnd.x, uvEnd.y};

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glActiveTexture(GL_TEXTURE0);
    texture.Use();

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::Draw(Atlas atlas, glm::vec2 position, glm::vec2 size,
                          float rotate, glm::vec3 color, SpriteID sprite, int frameIndex)
{
    m_shader.Use();

    Texture2D &texture = ResourceManager::GetTexture("shroom");
    texture.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "model"), 1, GL_FALSE, &model[0][0]);

    Sprite s = getSprite(sprite);
    // Calculate UVs for the current frame
    glm::vec2 frameOffset = s.offSet + glm::vec2(frameIndex * s.subSize.x, 0);
    glm::vec2 uvStart(frameOffset.x / texture.m_width, frameOffset.y / texture.m_height);
    glm::vec2 uvEnd((frameOffset.x + s.subSize.x) / texture.m_width,
                    (frameOffset.y + s.subSize.y) / texture.m_height);

    float vertices[]{
        // Pos     //UV
        0.0f, 1.0f, uvStart.x, uvStart.y,
        1.0f, 0.0f, uvEnd.x, uvEnd.y,
        0.0f, 0.0f, uvStart.x, uvEnd.y,

        0.0f, 1.0f, uvStart.x, uvStart.y,
        1.0f, 1.0f, uvEnd.x, uvStart.y,
        1.0f, 0.0f, uvEnd.x, uvEnd.y};

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawLine(Shader &shader, float first_x, float first_y, float second_x, float second_y)
{
    shader.Use();

    float vertices[] = {
        first_x, first_y,
        second_x, second_y
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_LINES, 0, 2);
}

void SpriteRenderer::initData()
{

    float vertices[]{
        // Position      //Texture UV's
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f

    };

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::initDataNoUV()
{

    float vertices[]{
        // Position      //Texture UV's
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f

    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
