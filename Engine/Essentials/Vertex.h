





#pragma once
#include <glm/glm.hpp>
#include <vector>  /

struct Vertex
{
    glm::vec2 Position;   // 2D position (x, y)
    glm::vec2 TexCoord;   // Texture coordinates (u, v)
    glm::vec4 Color;      // Optional: RGBA color

    Vertex() = default;

    Vertex(const glm::vec2& pos, 
           const glm::vec2& uv,
           const glm::vec4& color = {1.0f, 1.0f, 1.0f, 1.0f})
        : Position(pos), TexCoord(uv), Color(color) {}
};

class Vertices {
public:
    Vertices() = default;

    // Add a single vertex
    void Add(const Vertex& v) {
        m_data.push_back(v);
    }

    // Add many vertices at once
    void Add(const std::vector<Vertex>& verts) {
        m_data.insert(m_data.end(), verts.begin(), verts.end());
    }

    // Clear all vertices
    void Clear() {
        m_data.clear();
    }

    // How many vertices?
    size_t Count() const { return m_data.size(); }

    // Raw pointer for glBufferData
    const Vertex* Raw() const {
        return m_data.data();
    }

    // Vector accessor
    const std::vector<Vertex>& Data() const {
        return m_data;
    }

private:
    std::vector<Vertex> m_data;
};
