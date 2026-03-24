
#pragma once
#include "Platform/Event.h"

namespace FrostEngine
{
    struct AppSpec
    {
        int width = 0;
        int height = 0;
        const char *name = "default";
        bool vsync = true;
    };

    class Application
    {
    public:
        explicit Application(const AppSpec &spec);
        virtual ~Application() = default;

        const AppSpec &GetSpec() const;

        virtual void Init() {}
        virtual void OnEvent(const Event &e) {}
        virtual void Update(double dt) {}
        virtual void Render(double alpha) {}
        virtual void Shutdown() {}

    private:
        AppSpec m_spec;
    };

    void Run(Application &app);
}