#include <drn/scene.hpp>
#include <SDL2/SDL_opengl.h>

#include <math.h>
#include <cmath>
#include <iostream>

namespace drn {
    extern Window* WindowPT;
}

using namespace drn;

Window* drn::WindowPT = nullptr;

void Debug_Log(std::string string) {
    std::cout << "LOG: " << string << std::endl;
}

void Debug_Warn(std::string string) {
    std::cout << "\x1b[33mWARN: " << string << "\x1b[0m" << std::endl;
}

void Debug_Error(std::string string) {
    std::cout << "\x1b[31mERROR: " << string << "\x1b[0m" << std::endl;
}

// SCENES

LLScene::LLScene(int initfunc (), int drawfunc (), int updatefunc ()) {
    M_InitPF = initfunc;
    M_DrawPF = drawfunc;
    M_UpdatePF = updatefunc;
}

void HLScene::Update() {
    // Camera Rotation Correction so we do not go over the max values
    if (CameraRot.X > M_PI*2) CameraRot.X -= M_PI*2;
    if (CameraRot.X < 0) CameraRot.X += M_PI*2;
    if (CameraRot.Y > M_PI*2) CameraRot.Y -= M_PI*2;
    if (CameraRot.Y < 0) CameraRot.Y += M_PI*2;
    if (CameraRot.Z > M_PI*2) CameraRot.Z -= M_PI*2;
    if (CameraRot.Z < 0) CameraRot.Z += M_PI*2;

    // Camera Updates
    for (Node* n : WorldComponents) n->update();
}

// WINDOW CLASS

Window::Window(std::string title, i32 width, i32 height) {
    m_CurrentDT = 0;
    m_WindowName = title;
    m_windowWidth = width;
    m_windowHeight = height;

    WindowPT = this;
}

void Window::LoadScene(Scene* s) {
    m_CurrentScene = s;
    m_CurrentScene->Init();
}

int Window::Init(Scene* s) {
    Debug_Log("Sample Normal Log Message");
    Debug_Warn("Sample Log Warning Message");
    Debug_Error("Sample Error Message");
    
    // Initializing SDL
    Debug_Log("Initializing SDL Window");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Debug_Error("Unable to Initialize SDL");
        return 1;
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

    m_window = SDL_CreateWindow(m_WindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (m_window == NULL) {
        Debug_Error("Unable to Create SDL Window");
        return -1;
    }

    // Initializing OpenGL Contenxt
    Debug_Log("Initializing OpenGL Context");
    m_glContext = SDL_GL_CreateContext(m_window);
    if (SDL_GL_SetSwapInterval(1) < 0) Debug_Warn("Unable to set VSync");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Load Initial Scene
    Debug_Log("Loading Scene");
    LoadScene(s);

    return 0;
}

// Rewrite
float Window::getDT() {
    return 0;
}

void Window::Loop() {
    SDL_Event e;
    bool quit = false;
    
    while (!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }

        m_CurrentScene->Update();

        glClear(GL_COLOR_BUFFER_BIT);
        m_CurrentScene->Draw();
        SDL_GL_SwapWindow(m_window);
    }

    SDL_DestroyWindow(m_window);

    SDL_Quit();
}

// Projection Equations

Vec2<int> HLScene::ProjectPerspective(Vec3<float> pos) {
    // Displaces the position in respect to where the camera is
    Vec3<float> dPos = pos-CameraPos;

    // Displace the object in respect to the rotation of the camera
    // Rotation Equation Taken from [Wikipedia](https://en.wikipedia.org/wiki/3D_projection)
    Vec3<float> fPos = {
        cos(CameraRot.Y)*(sin(CameraRot.Z)*dPos.Y+cos(CameraRot.Z)*dPos.X)-sin(CameraRot.Y)*dPos.Z,
        sin(CameraRot.X)*(cos(CameraRot.Y)*dPos.Z)+sin(CameraRot.Y)*(sin(CameraRot.Z)*dPos.Y+cos(CameraRot.Z)*dPos.X)+cos(CameraRot.X)*(cos(CameraRot.Z)*dPos.Y-sin(CameraRot.Z)*dPos.X),
        cos(CameraRot.X)*(cos(CameraRot.Y)*dPos.Z)+sin(CameraRot.Y)*(sin(CameraRot.Z)*dPos.Y+cos(CameraRot.Z)*dPos.X)-sin(CameraRot.Z)*(cos(CameraRot.Z)*dPos.Y-sin(CameraRot.Z)*dPos.X),
    };

    return {(int)((fPos.X*WindowPT->GetWindowDimensions().X)/(WindowPT->GetWindowDimensions().X*fPos.Z/60)), (int)((fPos.Y*WindowPT->GetWindowDimensions().Y)/(WindowPT->GetWindowDimensions().Y*fPos.Z/60))};
}