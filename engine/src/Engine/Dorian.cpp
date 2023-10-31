#include <drn/scene.hpp>
#include <drn/input.hpp>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <math.h>
#include <cmath>
#include <iostream>

namespace drn {
    extern Window* WindowPT;
}

extern std::vector<GLfloat> VertexData;
extern std::vector<GLuint> indexData;
extern std::vector<GLfloat> meshNormals;
extern int vertexCounter;

std::vector<GLfloat> VertexData{};
std::vector<GLuint> indexData{};
std::vector<GLfloat> meshNormals{};

using namespace drn;

Window* drn::WindowPT = nullptr;

//--------//
// SCENES //
//--------//

LLScene::LLScene(int initfunc (), int drawfunc (), int updatefunc ()) {
    M_InitPF = initfunc;
    M_DrawPF = drawfunc;
    M_UpdatePF = updatefunc;
}

void HLScene::Draw() {
    for (Node* n : WorldComponents) {
        // Prepare OpenGL Components
        VertexData.clear();
        indexData.clear();
        vertexCounter = 0;
        
        // Call The Draw Function
        n->draw();

        // Call OpenGL Buffer and Draw Call if there is anything to draw
        if (VertexData.size() != 0) {
            GLuint gVBO{0}; // Vertecies Buffer Object
            GLuint gIBO{0}; // Indecies Buffer Object
            GLuint gNBO{0}; // Normals Buffer Object

            glGenBuffers(1, &gVBO);
            glBindBuffer(GL_ARRAY_BUFFER, gVBO);
            glBufferData(GL_ARRAY_BUFFER, 2*indexData.size()*sizeof(GLfloat), &VertexData[0], GL_STATIC_DRAW);

            glGenBuffers(1, &gIBO);
            glBindBuffer(GL_ARRAY_BUFFER, gIBO);
            glBufferData(GL_ARRAY_BUFFER, indexData.size()*sizeof(GLuint), &indexData[0], GL_STATIC_DRAW);

            GLint gVertexPos2DLocation = glGetAttribLocation(CurrentShader->getProgramID(), "VertexPos");

            glEnableVertexAttribArray(gVertexPos2DLocation);

            glBindBuffer( GL_ARRAY_BUFFER, gVBO );
	        glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

            // Attaching Normals

            //GLint gMeshNormalsAttr = glGetAttribLocation(CurrentShader->getProgramID(), "fNormal");
            //glBindAttribLocation(CurrentShader->getProgramID(), )
            //glAttrib

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
            glDrawElements( GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, NULL );
        }
    }
}

//--------------//
// WINDOW CLASS //
//--------------//

Window::Window(std::string title, i32 width, i32 height) {
    m_CurrentDT = 0;
    m_WindowName = title;
    m_windowWidth = width;
    m_windowHeight = height;

    WindowPT = this;
}

void Window::LoadScene(Scene* s) {
    //Unloads Scene first. Maybe. Still need to decide if objects unload data
    //if (m_CurrentScene != nullptr);
    m_CurrentScene = s;
    m_CurrentScene->Init();
}

Shader drn::DefaultShader;

int Window::Init(Scene* s) {
    Debug_Log("Dorian Engine - Built on " << __DATE__ << " at approximately " << __TIME__);
    Debug_Log("Sample Normal Log Message");
    Debug_Warn("Sample Log Warning Message");
    Debug_Error("Sample Error Message");
    
    // Initializing SDL
    Debug_Log("Initializing SDL");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Debug_Error("Unable to Initialize SDL");
        return 1;
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    m_window = SDL_CreateWindow(m_WindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (m_window == NULL) {
        Debug_Error("Unable to Create SDL Window");
        return -1;
    }

    // Initializing OpenGL Contenxt
    Debug_Log("Initializing OpenGL Context");
    m_glContext = SDL_GL_CreateContext(m_window);
    if (SDL_GL_SetSwapInterval(1) < 0) Debug_Warn("Unable to set VSync");

    // Initialize GLEW
    Debug_Log("Initializing GLEW");
    glewInit();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Load Initial Scene
    Debug_Log("Initializing Shaders");
    drn::DefaultShader = Shader(DefaultFragmentShader);

    Debug_Log("Loading Scene");
    LoadScene(s);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return 0;
}

// Requires Rewrite
double Window::getDT() {
    return m_CurrentDT;
}

void Window::Loop() {
    SDL_Event e;
    bool quit{false};
    
    // Initializing DeltaTime
    m_CurrentDT = 0;
    double LoopStart{}, LoopEnd{0};

    while (!quit) {
        LoopStart = LoopEnd;

        // Event Callbacks
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                // This should implement fine for now...
                // However, this is repetitive, and we also need to implement sudden key presses and releases.
                // Because of that, this may need to be reimplemented in the future.
                switch (e.key.keysym.sym) {
                    case DORIAN_LUP:
                    KeyboardInput.on(LUp);
                    break;
                    case DORIAN_LDOWN:
                    KeyboardInput.on(LDown);
                    break;
                    case DORIAN_LLEFT:
                    KeyboardInput.on(LLeft);
                    break;
                    case DORIAN_LRIGHT:
                    KeyboardInput.on(LRight);
                    break;
                    case DORIAN_START:
                    KeyboardInput.on(Start);
                    break;
                    case DORIAN_SELECT:
                    KeyboardInput.on(Select);
                    break;
                    case DORIAN_A:
                    KeyboardInput.on(A);
                    break;
                    case DORIAN_B:
                    KeyboardInput.on(B);
                    break;
                    case DORIAN_X:
                    KeyboardInput.on(X);
                    break;
                    case DORIAN_Y:
                    KeyboardInput.on(Y);
                    break;

                }
            }
            else if (e.type == SDL_KEYUP) {
                // Same as SDL_KEYDOWN, but for SDL_KEYUP
                switch (e.key.keysym.sym) {
                    case DORIAN_LUP:
                    KeyboardInput.off(LUp);
                    break;
                    case DORIAN_LDOWN:
                    KeyboardInput.off(LDown);
                    break;
                    case DORIAN_LLEFT:
                    KeyboardInput.off(LLeft);
                    break;
                    case DORIAN_LRIGHT:
                    KeyboardInput.off(LRight);
                    break;
                    case DORIAN_START:
                    KeyboardInput.off(Start);
                    break;
                    case DORIAN_SELECT:
                    KeyboardInput.off(Select);
                    break;
                    case DORIAN_A:
                    KeyboardInput.off(A);
                    break;
                    case DORIAN_B:
                    KeyboardInput.off(B);
                    break;
                    case DORIAN_X:
                    KeyboardInput.off(X);
                    break;
                    case DORIAN_Y:
                    KeyboardInput.off(Y);
                    break;

                }
            }
        }

        // General Updates
        m_CurrentScene->Update();

        // Drawing
        glClear(GL_COLOR_BUFFER_BIT);
        m_CurrentScene->Draw();
        SDL_GL_SwapWindow(m_window);

        // Finishing Calculations for DeltaTime
        LoopEnd = SDL_GetPerformanceCounter();
        m_CurrentDT = (LoopEnd - LoopStart)/(double)SDL_GetPerformanceFrequency();
    }

    SDL_DestroyWindow(m_window);

    SDL_Quit();
}

// Projection Equations

/*
[[CAMERA COMPONENT NEEDS REWRITE]]

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
} */