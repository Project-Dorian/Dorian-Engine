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
    "layout(location = 0) in vec3 VertexPos;\n"
    "layout(location = 1) in vec3 VertexColor;\n"
    "out vec3 FragVertexColor;\n"
    "void main()\n"
    "{\n"
    "   FragVertexColor = VertexColor;\n"
    "   gl_Position = vec4(VertexPos, 1);\n"
    "}\0"
};

GLchar* drn::DefaultFragmentShader[]{
    "#version 330 core\n"
    "in vec3 FragVertexColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(FragVertexColor, 1.0);\n"
    "}\n"
};

extern std::vector<GLfloat> VertexData;
extern std::vector<GLuint> indexData;
extern std::vector<GLfloat> normalMaps;
extern std::vector<GLfloat> textureCoords;

extern int vertexCounter;
int vertexCounter{0};

int FindVertex(Vec3<GLfloat> coords) {
    if (VertexData.size() == 0) return -1;

    for (int i = 0; i < VertexData.size()/2; i++) {
        if ((coords.X == VertexData[6*i] && coords.Y == VertexData[6*i+1]) && coords.Z == VertexData[6*i+2]) return i;
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
    drn::DrawPlane({a.X, a.Y, 1.0f}, {b.X, b.Y, 1.0f}, {c.X, c.Y, 1.0f}, {d.X, d.Y, 1.0f});
}

void drn::DrawPlane(Vec3<float> a, Vec3<float> b, Vec3<float> c, Vec3<float> d) {
    // Setting up Vertex and Index Data

    // X, Y, Z, Vertex R, Vertex G, Vertex B
    GLfloat GeneratedVertexData[] = {
        (a.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-a.Y*2/WindowPT->GetWindowDimensions().Y)+1.f, (-a.Z/60), 1.0f, 0.0f, 0.0f,
        (b.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-b.Y*2/WindowPT->GetWindowDimensions().Y)+1.f, (-b.Z/60), 0.0f, 1.0f, 0.0f,
        (c.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-c.Y*2/WindowPT->GetWindowDimensions().Y)+1.f, (-c.Z/60), 0.0f, 0.0f, 1.0f,
        (d.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-d.Y*2/WindowPT->GetWindowDimensions().Y)+1.f, (-d.Z/60), 1.0f, 1.0f, 1.0f
    };

    int indexOrder[] = {0, 1, 2, 3, 2, 1};

    // This makes sure vertex positions are not reused
    for (int i = 0; i < 6; i++) {
        int VertexExists{FindVertex({GeneratedVertexData[6*indexOrder[i]], GeneratedVertexData[6*indexOrder[i]+1], GeneratedVertexData[6*indexOrder[i]+2]})};
        if (VertexExists != -1) {
            indexData.push_back(VertexExists);
            continue;
        }

        indexData.push_back(vertexCounter++);
        
        // Push New Vertices
        VertexData.push_back(GeneratedVertexData[6*indexOrder[i]]);
        VertexData.push_back(GeneratedVertexData[6*indexOrder[i]+1]);
        VertexData.push_back(GeneratedVertexData[6*indexOrder[i]+2]);
        VertexData.push_back(GeneratedVertexData[6*indexOrder[i]+3]);
        VertexData.push_back(GeneratedVertexData[6*indexOrder[i]+4]);
        VertexData.push_back(GeneratedVertexData[6*indexOrder[i]+5]);
    }
}