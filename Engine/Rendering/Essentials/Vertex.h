#pragma once
#include "glad/glad.h"
#include "FrostMath.h"

namespace FrostEngine
{
    struct Color
    {
        GLubyte r, g, b, a;
        Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
        :r(r), b(b), g(g), a(a)
        {

        }
        //unsigned byte s;
    };

    struct Vertex
    {
        vec2 position {0.f}, uvs {0.f};
        Color color{255, 255, 0, 255};
        void set_color(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
        {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }
    };
}