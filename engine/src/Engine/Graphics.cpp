#include <drn/graphics.hpp>

#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

#include <exception>
#include <iostream>

namespace drn {
    extern Window* WindowPT;
}

using namespace drn;

GLuint drn::DefaultVertexShader;
GLuint drn::DefaultFragmentShader;
GLuint drn::gProgramID;

const GLchar* defaultVertexShaderCode[]{
        "#version 330 core\n"
        "in vec2 vertexPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(vertexPos.x, vertexPos.y, 0, 1);\n"
        "}\0"
    };

const GLchar* defaultFragmentShaderCode[]{
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n"
};

int drn::InitGLShaders() {
    Debug_Log("Initializing Default Shaders");
    drn::gProgramID = glCreateProgram();

    drn::DefaultVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(DefaultVertexShader, 1, defaultVertexShaderCode, NULL);
    glCompileShader(DefaultVertexShader);

    GLint compileSuccess = GL_FALSE;
    glGetShaderiv(DefaultVertexShader, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess != GL_TRUE) Debug_Warn("Vertex Shader Compile Failed");

    glAttachShader(gProgramID, DefaultVertexShader);

    drn::DefaultFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(DefaultFragmentShader, 1, defaultFragmentShaderCode, NULL);
    glCompileShader(DefaultFragmentShader);

    glGetShaderiv(DefaultFragmentShader, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess != GL_TRUE) Debug_Warn("Fragment Shader Compile Failed");

    glAttachShader(gProgramID, DefaultFragmentShader);

    glLinkProgram(gProgramID);
    
    return 0; 
}

void drn::DrawRect(Vec2<float> pos, Vec2<float> size) {
    // Repositioning Adjustments for OpenGL
    Vec2<float> newPos{pos.X*2/WindowPT->GetWindowDimensions().X, -pos.Y*2/WindowPT->GetWindowDimensions().Y};
    Vec2<float> newSize{size.X*2/WindowPT->GetWindowDimensions().X, size.Y*2/WindowPT->GetWindowDimensions().Y};

    // Setting up Vertex and Index Data
    GLfloat VertexData[] = {
        newPos.X-1.f, newPos.Y+1.f,
        newPos.X+newSize.X-1.f, newPos.Y+1.f,
        newPos.X+newSize.X-1.f, newPos.Y-newSize.Y+1.f,
        newPos.X-1.f, newPos.Y-newSize.Y+1.f
    };

    GLuint indexData[] = {0, 1, 2, 3};

    GLuint gVBO{0};
    GLuint gIBO{0};

    // Random B******t Go
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(GLfloat), VertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &gIBO);
    glBindBuffer(GL_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLuint), indexData, GL_STATIC_DRAW);

    GLint gVertexPos2DLocation = glGetAttribLocation( gProgramID, "vertexPos" );

    glUseProgram(gProgramID);

    glEnableVertexAttribArray(gVertexPos2DLocation);

    glBindBuffer( GL_ARRAY_BUFFER, gVBO );
	glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
    glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

    //glDisableVertexAttribArray( gVertexPos2DLocation );
    //glUseProgram(NULL);
}

void drn::DrawQuad(Vec2<float> a, Vec2<float> b, Vec2<float> c, Vec2<float> d) {
    // Setting up Vertex and Index Data
    GLfloat VertexData[] = {
        (a.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-a.Y*2/WindowPT->GetWindowDimensions().Y)+1.f,
        (b.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-b.Y*2/WindowPT->GetWindowDimensions().Y)+1.f,
        (c.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-c.Y*2/WindowPT->GetWindowDimensions().Y)+1.f,
        (d.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-d.Y*2/WindowPT->GetWindowDimensions().Y)+1.f
    };

    GLuint indexData[] = {0, 1, 2, 3};

    GLuint gVBO{0};
    GLuint gIBO{0};

    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(GLfloat), VertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &gIBO);
    glBindBuffer(GL_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLuint), indexData, GL_STATIC_DRAW);

    GLint gVertexPos2DLocation = glGetAttribLocation(gProgramID, "vertexPos");

    glUseProgram(gProgramID);

    glEnableVertexAttribArray(gVertexPos2DLocation);

    glBindBuffer( GL_ARRAY_BUFFER, gVBO );
	glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
    glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

    //glDisableVertexAttribArray( gVertexPos2DLocation );
    //glUseProgram(NULL);
}