#include "SpriteBatchRenderer.h"
#include "algorithm"

SpriteBatchRenderer::SpriteBatchRenderer()
{
    FROST_LOG("CREATED BATCH REN");
    Init();
}

void SpriteBatchRenderer::Init()
{

    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_VERTICES, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    unsigned int arr[MAX_INDICES]{};
    int offset{};
    for (size_t i = 0; i < MAX_INDICES; i += INDICES_PER_QUAD)
    {
        for (size_t j = 0; j < INDICES_PER_QUAD; j++)
        {
            arr[i + j] = indices[j] + offset;
        }
        offset += VERTS_PER_QUAD;
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * MAX_INDICES, arr, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void SpriteBatchRenderer::DrawSprite(const vec3 &position, const vec2 &size, float rotation, const Sprite &sprite, float atlasWidth,
                                     float atlasHeight, const vec4 color)
{
    // 1. Check if we need to flush the batch BEFORE adding new vertices
    if (m_VertexCount + 4 > MAX_VERTICES)
        Render();

    // 2. Calculate Z-Depth sorting value on the CPU
    // We use the input 'position.y' to determine depth
    float sortY = position.y + size.y * 0.5f;

    // clamp to avoid going outside 0..1
    sortY = std::clamp(sortY, 0.0f, 720.0f);

    float depth = sortY / 720.0f;

    vec2 halfSize = size * 0.5f;

    // Local coordinates of the quad corners
    vec2 localPositions[4] = {
        {-halfSize.x, halfSize.y}, // bottom left
        {halfSize.x, halfSize.y},  // bottom right
        {halfSize.x, -halfSize.y}, // top right
        {-halfSize.x, -halfSize.y} // top left
    };

    float c = cos(rotation);
    float s = sin(rotation);

    // Rotation helper (Rotates X and Y, leaves Z alone)
    auto GetWorldPos = [&](vec2 lp)
    {
        float rx = lp.x * c - lp.y * s;
        float ry = lp.x * s + lp.y * c;
        // Combine rotated offset with world position and our calculated depth
        return vec3{position.x + rx, position.y + ry, depth};
    };

    // UV Calculation
    vec2 uvMin = {
        sprite.uv.x / atlasWidth,
        1.0f - (sprite.uv.y + sprite.size.y) / atlasHeight  // ← flip Y, start from bottom of sprite
    };

    vec2 uvMax = {
        (sprite.uv.x + sprite.size.x) / atlasWidth,
        1.0f - sprite.uv.y / atlasHeight                     // ← flip Y, end at top of sprite
    };

    vec2 uvs[4] = {
        {uvMin.x, uvMin.y},
        {uvMax.x, uvMin.y},
        {uvMax.x, uvMax.y},
        {uvMin.x, uvMax.y}};

    // 3. Add to vertex array
    for (int i = 0; i < 4; i++)
    {
        m_Vertices[m_VertexCount++] = {
            GetWorldPos(localPositions[i]),
            uvs[i],
            color};
    }

    m_IndicesCount += 6;
}

void SpriteBatchRenderer::genVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_VertexCount, m_Vertices.data());
}

// void SpriteBatchRenderer::Render()
// {
//     genVBO();
//     glBindVertexArray(m_VAO);
//     // glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     // glDrawArrays(GL_TRIANGLES, 0, vertex_count);
//     glEnable(GL_DEPTH_TEST);
//     glDepthFunc(GL_LEQUAL);
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, 0);
//     flush();
// }
void SpriteBatchRenderer::Render()
{
    if (m_IndicesCount == 0)
        return; // Don't draw if batch is empty

    //m_Shader->Bind();
    // Update uProjection here if it changed (or once at start of frame)

    genVBO(); // Upload all vertices at once
    glBindVertexArray(m_VAO);

    glEnable(GL_DEPTH_TEST);
    // TIE BREAKER: Newer sprites in the batch win if Y is identical
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // DRAW EVERYTHING IN ONE SHOT
    glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, 0);

    flush(); // Reset vertex_count and indices_count to 0
}

void SpriteBatchRenderer::flush()
{

    m_Vertices.fill({{0}, {0}});
    m_VertexCount = 0;
    m_IndicesCount = 0;
}