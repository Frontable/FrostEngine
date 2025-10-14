





#include "Game.h"
#include <iostream>
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "Test.h"



Box box(10,10,100,100);
Ent ent1(5,4);
Ent ent2(15,15);
Ent ent3(105, 15);

//TestSystem test;



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
    ResourceManager::LoadShader("../data/Shaders/Shader.vert", "../data/Shaders/Shader.frag", "line");
    Shader& shader = ResourceManager::GetShader("shader").Use();
    ResourceManager::LoadTexture("../data/images/awesomeface.png", "face");   
    ResourceManager::LoadTexture("../data/images/shroom.png", "shroom");   
    ResourceManager::LoadTexture("../data/images/atlas.png", "atlas"); 
    ResourceManager::LoadTexture("../data/images/background.jpg", "background"); 

    glm::mat4 projection = glm::ortho(0.0f, float(Width), float(Height), 0.0f, -1.0f , 1.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);    

    glm::vec2 pos(500), size(100), vel(200);
    player = new GameObject(pos, size, vel,SHROOM_SPRITE, 2);

    Entity entityOne = ecs->entityManager->CreateEntity();
    Entity entityTwo = ecs->entityManager->CreateEntity();
    ecs->entityManager->DeleteEntity(entityOne);
    Entity entityThree = ecs->entityManager->CreateEntity();
    ecs->entityManager->DeleteEntity(5);
    ecs->add(entityTwo);
    ecs->add(entityThree);

    ecs->componentManager->RegisterComponent<Fuck>();
    ecs->componentManager->RegisterComponent<Fuck>();
    ecs->componentManager->RegisterComponent<Transform>();
    //std::cout<<componentManager.m_componentArrays.size()<<std::endl;
    Transform transform{glm::vec2(100), glm::vec2(100), 0};
    ecs->componentManager->AddComponent<Transform>(entityOne, transform);
    ecs->componentManager->AddComponent<Transform>(entityTwo, transform);
    ecs->componentManager->AddComponent<Transform>(entityThree, transform);
    
    box.addEnt(&ent1);
    box.addEnt(&ent2);
    box.addEnt(&ent3);

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
    ecs->Update(dt);
    box.Update();
}

void Game::Render()
{
    SpriteRenderer::GetInstance()->DrawSpriteUV(ResourceManager::GetTexture("background"), glm::vec2(0), glm::vec2(800,600), 0, glm::vec3(1), BACKGROUND, 1);
    player->Draw();
    //SpriteRenderer::GetInstance()->DrawLine(ResourceManager::GetShader("line"), -0.5f, -0.5, 0.5, 0.5);
}

void Game::ShutDown()
{
    delete player;
    ResourceManager::Clean();
    if (window->GetNativeWindow())
        delete window;
    glfwTerminate();
}

