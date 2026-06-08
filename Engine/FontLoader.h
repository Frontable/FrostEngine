#pragma once
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <unordered_map>
#include <string>
#include "FrostMath.h"

namespace FrostEngine
{
    struct Glyph
    {
        vec2  uvMin;       // normalized UV top-left in atlas
        vec2  uvMax;       // normalized UV bottom-right in atlas
        vec2  size;        // size of glyph in pixels
        vec2  bearing;     // offset from baseline to top-left of glyph
        float advance;     // horizontal advance to next glyph
    };

    class FontLoader
    {
    public:
        FontLoader() = default;
        ~FontLoader();

        bool Load(const char* fontPath, unsigned int fontSize = 32);

        const Glyph& GetGlyph(char c) const { return m_Glyphs.at(c); }
        unsigned int GetAtlasID() const { return m_AtlasID; }
        float GetAtlasWidth()  const { return (float)m_AtlasWidth; }
        float GetAtlasHeight() const { return (float)m_AtlasHeight; }
        unsigned int GetFontSize() const { return m_FontSize; }

    private:
        std::unordered_map<char, Glyph> m_Glyphs;
        unsigned int m_AtlasID = 0;
        int          m_AtlasWidth = 0;
        int          m_AtlasHeight = 0;
        unsigned int m_FontSize = 32;
    };
}