#pragma once

#include "ECS/Components.h"
#include "FrostMath.h"
#include "Rendering/Essentials/Texture.h"
#include <array>
#include <vector>
#include "Logger/Logger.h"

static constexpr int MAX_SPRITES = 1000;
static constexpr int VERTS_PER_QUAD = 4;
static constexpr int INDICES_PER_QUAD = 6; // same
static constexpr int MAX_VERTICES = MAX_SPRITES * VERTS_PER_QUAD;
static constexpr int MAX_INDICES = MAX_SPRITES * INDICES_PER_QUAD; // gotta use it sometime

// void genUVs();

struct Vertex
{
    vec2 pos{0};
    vec2 uv{0};
    vec4 color{0};
};

// struct Batch
// {
//     // future idea to store multiple array of vertices depending on the texture we use
//     // to do figure it out
// };

class SpriteBatchRenderer
{
public:
    SpriteBatchRenderer();

    void Init();

    void DrawSprite(const vec2 &position, const vec2 &size, float rotation, const Sprite &sprite, float atlasWidth,
                    float atlasHeight, const vec4 color = vec4{1});
    
    void Render();

private:
    void genVBO();
    void flush();

    unsigned int m_VAO, m_VBO, m_EBO;
    std::array<Vertex, MAX_VERTICES> m_Vertices;
    int m_VertexCount = 0;
    int m_IndicesCount = 0;
};