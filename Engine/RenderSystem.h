#pragma once
#include "FrostMath.h"
//#include "Rendering/Essentials/Texture.h"
#include <array>
#include <vector>

static constexpr int MAX_SPRITES = 1000;
static constexpr int VERTS_PER_QUAD = 4;
static constexpr int INDICES_PER_QUAD = 6;//same
static constexpr int MAX_VERTICES = MAX_SPRITES * VERTS_PER_QUAD;
static constexpr int MAX_INDICES = MAX_SPRITES * INDICES_PER_QUAD; // gotta use it sometime

void genUVs();



struct Vertexx
{
    Vertexx(vec2 _pos, vec2 _uv):pos{_pos}, uv{_uv}{};
    Vertexx():Vertexx(vec2{0}, vec2{0}){}
    Vertexx(vec4 _pos, vec2 _uv):Vertexx(vec2( _pos.x, _pos.y), _uv){}
    vec2 pos{0};
    vec2 uv{0};
};
struct Sprite
{
    //Sprite():Sprite(vec2(0), vec2(0)){}
    Sprite(Vertexx _bl, Vertexx _br, Vertexx _tr, Vertexx _tl)
        :bl{_bl}, br{_br}, tr{_tr}, tl{_tl}{}
    //FrostEngine::Texture* tex;
    Vertexx bl, br, tr, tl;
};

struct Batch
{
    // future idea to store multiple array of vertices depending on the texture we use
    // to do figure it out
};

class SpriteBatchRenderer
{
public:
    int spritecount = 0;
    int vertex_count = 0;
    int indices_count = 0;

    unsigned int vao,vbo, ebo;

    std::vector<Sprite> m_sprites;
    
    std::array<Vertexx, MAX_VERTICES> m_vertices;
    void init()
    {
        // float ver[] =
        // {
        //     -0.5, -0.5,
        //      0.5, -0.5,
        //      0.5, 0.5,
        //      0.5, 0.5,
        //     -0.5, 0.5,
        //     -0.5, -0.5
        // };
        unsigned int indices[] = {0, 1, 2, 2, 3, 0};

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertexx) * MAX_VERTICES, nullptr, GL_DYNAMIC_DRAW);
        
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        unsigned int arr[MAX_INDICES]{};
        int offset{};
        for(size_t i = 0; i < MAX_INDICES; i += INDICES_PER_QUAD)
        {
            for(size_t j = 0; j < INDICES_PER_QUAD; j++)
            {
                arr[i + j] = indices[j] + offset;
            }
            offset += VERTS_PER_QUAD;
        }
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * MAX_INDICES, arr, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertexx), (void*)offsetof(Vertexx, pos));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertexx), (void*)offsetof(Vertexx, uv));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
    }
    void addSprite(const mat4& mat, const vec4& uvRect)
    {

        Sprite newSprite
        {
            Vertexx(vec4(mat * vec2(-0.5, -0.5)), vec2(uvRect.x, uvRect.y)),
            Vertexx{vec4(mat * vec2( 0.5, -0.5)), vec2{uvRect.x + uvRect.z, uvRect.y}},
            Vertexx{vec4(mat * vec2( 0.5,  0.5)), vec2{uvRect.x + uvRect.z, uvRect.y + uvRect.w}},
            Vertexx{vec4(mat * vec2(-0.5,  0.5)), vec2{uvRect.x, uvRect.y + uvRect.w}}        
        };

        m_sprites.emplace_back(newSprite);
        spritecount++;
        indices_count+=6;

    }

    void genVBO()
    {
        std::vector<Vertexx> vertices{};
        vertices.resize(m_sprites.size() * VERTS_PER_QUAD);
        int currentVertex = 0;
        for(auto& sprite : m_sprites)
        {
            vertices[currentVertex++] = sprite.bl;
            vertices[currentVertex++] = sprite.br;
            vertices[currentVertex++] = sprite.tr;
            vertices[currentVertex++] = sprite.tl;
        }

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertexx) * vertices.size(), vertices.data());

    }
    void render()
    {
        glBindVertexArray(vao);
        //glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //glDrawArrays(GL_TRIANGLES, 0, vertex_count);
        glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
    }
};