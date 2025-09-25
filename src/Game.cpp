





#include "Game.h"
#include <iostream>
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

unsigned int VAO;
glm::vec2 pos(100);
Animation playerAnim(2, 0.5f);
Animation shroomAnim(2, 0.5f);
//GameObject player(glm::vec2(500.0f), glm::vec2(32.0f), glm::vec2(100.0f), SHROOM_SPRITE, 2);


// Constructor
Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), window(nullptr), deltaTime(0.0f), lastFrame(0.0f)
{ 
    if(!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW\n");
    }

    window = new Window(width, height, "Engine");    

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


Game::~Game()
{
    
}

void Game::Init()
{

    Input::Init(window->GetNativeWindow());
    ResourceManager::LoadShader("../data/Shaders/Sprite.vert", "../data/Shaders/Sprite.frag", "shader");
    Shader& shader = ResourceManager::GetShader("shader").Use();
    ResourceManager::LoadTexture("../data/images/awesomeface.png", "face");   
    ResourceManager::LoadTexture("../data/images/shroom.png", "shroom");   
    ResourceManager::LoadTexture("../data/images/atlas.png", "atlas");   
    
    glm::mat4 projection = glm::ortho(0.0f, float(Width), float(Height), 0.0f, -1.0f , 1.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
    std::cout<<"Projection location: " << glGetUniformLocation(shader.ID, "projection") << std::endl;
    std::cout<<"Model location: " << glGetUniformLocation(shader.ID, "model") << std::endl;
    
    renderer = new SpriteRenderer(ResourceManager::GetShader("shader"));
    glm::vec2 pos(500), size(100), vel(200);
    player = new GameObject(pos, size, vel,SHROOM_SPRITE, 2, *renderer);
}


void Game::Run()
{
    while (!window->ShouldClose())
    {
        // calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window->PollEvents();

        ProcessInput(deltaTime);
        Update(deltaTime);

        // Render
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Render();        

        window->SwapBuffers();
    }
}

void Game::ProcessInput(float dt)
{
    
    if(Input::IsKeyPressed(GLFW_KEY_A))
        player->pos.x-= player->velocity.x * dt;

    if(Input::IsKeyPressed(GLFW_KEY_D))
        player->pos.x+= player->velocity.x * dt;

}

void Game::Update(float dt)
{
    playerAnim.Update(dt);
    shroomAnim.Update(dt);
    player->Update(dt);
}

void Game::Render()
{
    Texture2D& tex = ResourceManager::GetTexture("face");
    Texture2D& tex2 = ResourceManager::GetTexture("atlas");
    Texture2D& tex3 = ResourceManager::GetTexture("shroom");
    renderer->DrawSprite(tex, glm::vec2(100.0f), glm::vec2(100), 0.0f);
    renderer->DrawSpriteUV(tex2, pos, glm::vec2(64,64), 0.0f, glm::vec3(1), TEST, playerAnim.currentFrame);
    renderer->DrawSpriteUV(tex3, glm::vec2(200), glm::vec2(64,64), 0.0f, glm::vec3(1), SHROOM_SPRITE, shroomAnim.currentFrame);
    player->Draw();
}

void Game::ShutDown()
{
    delete player;
    delete renderer;
    ResourceManager::Clean();
    if (window->GetNativeWindow())
        delete window;
    glfwTerminate();
}

