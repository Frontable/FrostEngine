#include "FontLoader.h"
#include <iostream>
#include <vector>

namespace FrostEngine
{
    FontLoader::~FontLoader()
    {
        if (m_AtlasID)
            glDeleteTextures(1, &m_AtlasID);
    }

    bool FontLoader::Load(const char* fontPath, unsigned int fontSize)
    {
        m_FontSize = fontSize;

        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            std::cout << "[FontLoader] Failed to init FreeType\n";
            return false;
        }

        FT_Face face;
        if (FT_New_Face(ft, fontPath, 0, &face))
        {
            std::cout << "[FontLoader] Failed to load font: " << fontPath << "\n";
            FT_Done_FreeType(ft);
            return false;
        }

        FT_Set_Pixel_Sizes(face, 0, fontSize);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // --- Pass 1: measure atlas size ---
        m_AtlasWidth = 0;
        m_AtlasHeight = 0;

        for (unsigned char c = 32; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                continue;
            m_AtlasWidth += face->glyph->bitmap.width + 2; // 2px padding
            m_AtlasHeight = std::max(m_AtlasHeight, (int)face->glyph->bitmap.rows);
        }

        // --- Create atlas texture ---
        glGenTextures(1, &m_AtlasID);
        glBindTexture(GL_TEXTURE_2D, m_AtlasID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
            m_AtlasWidth, m_AtlasHeight,
            0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // --- Pass 2: upload glyphs into atlas ---
        int xOffset = 0;
        for (unsigned char c = 32; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                continue;

            auto& bmp = face->glyph->bitmap;

            glTexSubImage2D(GL_TEXTURE_2D, 0,
                xOffset, 0,
                bmp.width, bmp.rows,
                GL_RED, GL_UNSIGNED_BYTE,
                bmp.buffer);

            Glyph glyph;
            glyph.size = { (float)bmp.width, (float)bmp.rows };
            glyph.bearing = { (float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top };
            glyph.advance = (float)(face->glyph->advance.x >> 6);

            glyph.uvMin = { (float)xOffset / m_AtlasWidth,  0.0f };
            glyph.uvMax = { (float)(xOffset + bmp.width) / m_AtlasWidth,
                            (float)bmp.rows / m_AtlasHeight };

            m_Glyphs[c] = glyph;
            xOffset += bmp.width + 2;
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        std::cout << "[FontLoader] Loaded font: " << fontPath
            << " atlas: " << m_AtlasWidth << "x" << m_AtlasHeight << "\n";
        return true;
    }
}