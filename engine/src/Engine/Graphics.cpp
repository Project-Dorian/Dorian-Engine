#include <drn/graphics.hpp>

#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

#include <exception>
#include <iostream>

namespace drn {
    extern Window* WindowPT;
}

using namespace drn;

//-------------------//
// Initial Variables //
//-------------------//

// Shaders

GLchar* drn::DefaultVertexShader[]{
        "#version 330 core\n"
        "in vec2 VertexPos;\n"
        "out vec4 vertexColor;\n"
        "void main()\n"
        "{\n"
        "   vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
        "   gl_Position = vec4(VertexPos.x, VertexPos.y, 0, 1);\n"
        "}\0"
    };

GLchar* drn::DefaultFragmentShader[]{
    "#version 330 core\n"
    "in vec4 vertexColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(vertexColor.xyz, 1.0);\n"
    "}\n"
};

extern std::vector<GLfloat> VertexData;
extern std::vector<GLuint> indexData;
extern std::vector<GLfloat> normalMaps;
extern std::vector<GLfloat> textureCoords;

extern int vertexCounter;
int vertexCounter{0};

int FindVertex(Vec2<GLfloat> coords) {
    if (VertexData.size() == 0) return -1;

    for (int i = 0; i < VertexData.size()/2; i++) {
        if (coords.X == VertexData[2*i] && coords.Y == VertexData[2*i+1]) return i;
    }

    return -1;
}

//--------------//
// Shader Class //
//--------------//

drn::Shader::Shader(GLchar** FragmentCode, GLchar** VertexCode) {
    m_GLProgramID = glCreateProgram();

    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_VertexShader, 1, VertexCode, NULL);
    glCompileShader(m_VertexShader);

    GLint compileSuccess = GL_FALSE;
    glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess != GL_TRUE) Debug_Warn("Vertex Shader Compile Failed");

    glAttachShader(m_GLProgramID, m_VertexShader);

    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_FragmentShader, 1, FragmentCode, NULL);
    glCompileShader(m_FragmentShader);

    glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess != GL_TRUE) Debug_Warn("Fragment Shader Compile Failed");

    glAttachShader(m_GLProgramID, m_FragmentShader);

    glLinkProgram(m_GLProgramID);
}

Shader* drn::CurrentShader{&DefaultShader};

//-------------------//
// Drawing Functions //
//-------------------//


void drn::DrawRect(Vec2<float> pos, Vec2<float> size) {
    drn::DrawQuad(pos, {pos.X, pos.Y+size.Y}, {pos.X+size.X, pos.Y}, pos+size);
}

void drn::DrawQuad(Vec2<float> a, Vec2<float> b, Vec2<float> c, Vec2<float> d) {
    // Setting up Vertex and Index Data
    GLfloat GeneratedVertexData[] = {
        (a.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-a.Y*2/WindowPT->GetWindowDimensions().Y)+1.f,
        (b.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-b.Y*2/WindowPT->GetWindowDimensions().Y)+1.f,
        (c.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-c.Y*2/WindowPT->GetWindowDimensions().Y)+1.f,
        (d.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-d.Y*2/WindowPT->GetWindowDimensions().Y)+1.f
    };

    int indexOrder[] = {0, 1, 2, 3, 2, 1};

    for (int i = 0; i < 6; i++) {
        int VertexExists{FindVertex({GeneratedVertexData[2*indexOrder[i]], GeneratedVertexData[2*indexOrder[i]+1]})};
        if (VertexExists != -1) {
            indexData.push_back(VertexExists);
            continue;
        }

        indexData.push_back(vertexCounter++);
        VertexData.push_back(GeneratedVertexData[2*indexOrder[i]]);
        VertexData.push_back(GeneratedVertexData[2*indexOrder[i]+1]);
    }
}