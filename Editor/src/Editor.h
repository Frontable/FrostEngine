#include "Application.h"

#include "Rendering/Essentials/ShaderLoader.h"
#include "Rendering/Essentials/TextureLoader.h"


class Editor : public Application
{
    public:
    Editor();
    Editor(const char *_title, int _width, int _height);
    ~Editor(){}


    private:
    void Init() override;
    void Input() override;
    void Update() override;
    void Render() override;
    void Clean() override;

    
    
};
