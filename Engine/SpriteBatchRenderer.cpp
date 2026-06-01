#include "SpriteBatchRenderer.h"

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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void SpriteBatchRenderer::DrawSprite(const vec2 &position, const vec2 &size, float rotation, const Sprite &sprite, float atlasWidth,
                                     float atlasHeight, const vec4 color)
{
    if (m_VertexCount + 4 >= MAX_VERTICES)
        Render();

    vec2 halfSize = size * 0.5f;

    vec2 localPositions[4] =
        {
            {-halfSize.x, halfSize.y}, // bottom left
            {halfSize.x, halfSize.y},  // bottom right
            {halfSize.x, -halfSize.y}, // top right
            {-halfSize.x, -halfSize.y} // top left
        };

    float c = cos(rotation);
    float s = sin(rotation);

    auto Rotate = [&](vec2 p)
    {
        return vec2{
            p.x * c - p.y * s,
            p.x * s + p.y * c};
    };

    vec2 uvMin = {
        sprite.uv.x / atlasWidth,
        sprite.uv.y / atlasHeight};

    vec2 uvMax = {
        (sprite.uv.x + sprite.size.x) / atlasWidth,
        (sprite.uv.y + sprite.size.y) / atlasHeight};

    vec2 uvs[4] =
        {
            {uvMin.x, uvMin.y},
            {uvMax.x, uvMin.y},
            {uvMax.x, uvMax.y},
            {uvMin.x, uvMax.y}};

    for (int i = 0; i < 4; i++)
    {
        m_Vertices[m_VertexCount++] =
            {
                position + Rotate(localPositions[i]),
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

void SpriteBatchRenderer::Render()
{
    genVBO();
    glBindVertexArray(m_VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glDrawArrays(GL_TRIANGLES, 0, vertex_count);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, 0);
    flush();
}

void SpriteBatchRenderer::flush()
{

    m_Vertices.fill({{0}, {0}});
    m_VertexCount = 0;
    m_IndicesCount = 0;
}