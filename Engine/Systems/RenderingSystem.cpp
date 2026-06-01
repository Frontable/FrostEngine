// #include "RenderingSystem.h"
// #include "ECS/ECS.h"
// #include "Context.h"
// #include "Rendering/Core/Camera2D.h"
// //extern Context* m_mainContext;

// void RenderingSystem::init()
// {   
//     auto &camera = m_context.Get<FrostEngine::Camera2D>();
//     tex = FrostEngine::TextureLoader::Create(
//         FrostEngine::Texture::TextureType::BLENDED, 
//         "D:/Projects/FrostEngine/data/images/atlas.png");
//     shader = FrostEngine::ShaderLoader::Create(
//         "D:/Projects/FrostEngine/Engine/Assets/Shaders/basicV.glsl", 
//         "D:/Projects/FrostEngine/Engine/Assets/Shaders/basicF.glsl");
//     //cam = new FrostEngine::Camera2D{800,600};
//     //auto &cam = m_mainContext->Get<FrostEngine::Camera2D>();
//     renderer = new SpriteBatchRenderer{};
//     float vertices[] = {
//         -0.5f, -0.5f,
//          0.5f, -0.5f,
//          0.0f,  0.5f
//     };

//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }

// void RenderingSystem::Update()
// {
//     auto & m_ecs = m_context.Get<FrostEngine::ECS>();
//     if(!m_entities.empty())
//     {
//         auto &camm = m_context.Get<FrostEngine::Camera2D>();
//         glUseProgram(shader->ID()); 
//         glActiveTexture(0);
//         //shader->SetMatrix4x4("uProjection", cam->GetCameraMatrix());
//         shader->SetMatrix4x4("uProjection", camm.GetCameraMatrix());
//         shader->SetUniformInt("tex", 0);
//         tex->Bind();

//         for(auto &entity : m_entities)
//         {
//             auto &trans = m_ecs.GetComponent<Transform2D>(entity);
//             //renderer->addSprite(trans.GetModelMatrix(), vec4(0.0, 0.0, 1.0, 1.0));
//         }

//         renderer->render();
        
//     }    
// }