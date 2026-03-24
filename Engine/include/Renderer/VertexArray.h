#pragma once

#include "glad/glad.h"
#include <vector>
#include <cstddef>

namespace FrostEngine
{
    struct Vertex
    {
        float x, y;
        float u, v;
        float r, g, b;
    };

    struct VertexLayout
    {
        int index;
        unsigned int size;
        bool normalized;
        size_t stride;
        const void* ptr;
    };

    class VertexBuffer
    {
    public:
        VertexBuffer(const std::vector<Vertex>& vertices)
        {
            glGenBuffers(1, &m_id);
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        }

        ~VertexBuffer()
        {
            if (m_id)
                glDeleteBuffers(1, &m_id);
        }

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(VertexBuffer&& other) noexcept
            : m_id(other.m_id), m_layouts(std::move(other.m_layouts))
        {
            other.m_id = 0;
        }

        VertexBuffer& operator=(VertexBuffer&& other) noexcept
        {
            if (this != &other)
            {
                if (m_id)
                    glDeleteBuffers(1, &m_id);

                m_id = other.m_id;
                m_layouts = std::move(other.m_layouts);
                other.m_id = 0;
            }
            return *this;
        }

        void Bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
        }

        void Unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        unsigned int ID() const { return m_id; }

        void AddLayout(const VertexLayout& layout)
        {
            m_layouts.emplace_back(layout);
        }

        const std::vector<VertexLayout>& Layout() const
        {
            return m_layouts;
        }

    private:
        unsigned int m_id = 0;
        std::vector<VertexLayout> m_layouts;
    };

    class ArrayBuffer
    {
    public:
        ArrayBuffer()
        {
            glGenVertexArrays(1, &m_id);
        }

        ~ArrayBuffer()
        {
            if (m_id)
                glDeleteVertexArrays(1, &m_id);
        }

        ArrayBuffer(const ArrayBuffer&) = delete;
        ArrayBuffer& operator=(const ArrayBuffer&) = delete;

        void Bind() const
        {
            glBindVertexArray(m_id);
        }

        void Unbind() const
        {
            glBindVertexArray(0);
        }

        void AddBuffer(const VertexBuffer& buffer)
        {
            Bind();
            buffer.Bind();

            const auto& layouts = buffer.Layout();
            for (const auto& layout : layouts)
            {
                glEnableVertexAttribArray(layout.index);
                glVertexAttribPointer(
                    layout.index,
                    static_cast<GLint>(layout.size),
                    GL_FLOAT,
                    layout.normalized ? GL_TRUE : GL_FALSE,
                    static_cast<GLsizei>(layout.stride),
                    layout.ptr
                );
            }
        }

    private:
        unsigned int m_id = 0;
    };
}