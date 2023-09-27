#include <raylib.h>
#include <drn/scene.hpp>
using namespace drn;

// SCENES

LLScene::LLScene(int initfunc (), int drawfunc (int), int updatefunc (int)) {
    M_InitPF = initfunc;
    M_DrawPF = drawfunc;
    M_UpdatePF = updatefunc;
}

// WINDOW CLASS

Window::Window(std::string title, i32 width, i32 height) {
    m_CurrentDT = 0;
    m_WindowName = title;
    m_windowWidth = width;
    m_windowHeight = height;
}

void Window::LoadScene(Scene* s) {
    m_CurrentScene = s;
    m_CurrentScene->Init();
}

void Window::Init(Scene* s) {
    LoadScene(s);

    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(m_windowWidth, m_windowHeight, m_WindowName.c_str());
    SetTargetFPS(60);
    InitAudioDevice();
}

float Window::getDT() {
    return GetFrameTime();
}

void Window::Loop() {
    
    while (!WindowShouldClose()) {
        m_CurrentScene->Update();

        BeginDrawing();
        ClearBackground(BLACK);
        m_CurrentScene->Draw();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
}