





#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Input.h"
#include "SpriteRenderer.h"
#include "ECS.h"
#include "GameObject.h"
//#include "SystemManager.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};


class Game
{
public:
    GameState State;
    bool Keys[1024];
    unsigned int Width, Height;
    Window* window = nullptr;
    GameObject* player;
    ECS* ecs = ECS::getInstance();
     

    float deltaTime;
    float lastFrame;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void Init();
    void Run();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void ShutDown();
};

// Callbacks
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
