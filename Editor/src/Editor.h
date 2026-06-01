#include "Application.h"

#include "Rendering/Essentials/ShaderLoader.h"
#include "Rendering/Essentials/TextureLoader.h"
#include "FrostMath.h"

class Editor : public Application
{
    public:
    Editor();
    Editor(const char *_title, int _width, int _height);
    ~Editor(){}


    private:
    void Init() override;
    void Input(float dt) override;
    void Update(float dt) override;
    void Render(float dt) override;
    void Clean() override;
    float rotate = 0;
    vec2 pos{0};
    void loadSystems();
    
    
};
