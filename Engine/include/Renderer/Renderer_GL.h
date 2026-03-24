#include "Renderer/RendererAPI.h"

#include "Math/Math.h"
#include <vector>


namespace FrostEngine
{
    class Renderer_GL : public RendererAPI
    {
    public:

        ~Renderer_GL()
        {

        }
        void RendererSetClearColor(float r, float g, float b, float a) override;

        void RendererSetClearColor(vec4 color) override;
        void RendererClear(unsigned int mask) override;

        void drawQuad(vec2 pos, vec2 size) override;


        void AddShader() override;

    private:
    };
}