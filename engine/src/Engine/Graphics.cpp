#include <drn/graphics.hpp>

#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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
    "layout(location = 2) in vec2 TexCoord;\n"
    "out vec3 FragVertexColor;\n"
    "out vec2 FragTexCoord;\n"
    "void main()\n"
    "{\n"
    "   FragVertexColor = VertexColor;\n"
    "   FragTexCoord = TexCoord;\n"
    "   gl_Position = vec4(VertexPos, 1);\n"
    "}\0"
};

GLchar* drn::DefaultFragmentShader[]{
    "#version 330 core\n"
    "in vec3 FragVertexColor;\n"
    "in vec2 FragTexCoord;\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D tex0;\n"
    "void main()\n"
    "{\n"
    "    FragColor = texture(tex0, FragTexCoord);\n"
    //"   FragColor = vec4(FragTexCoord.xy, 0.0f, 1.0f);"
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

    for (int i = 0; i < VertexData.size()/8; i++) {
        if ((coords.X == VertexData[8*i] && coords.Y == VertexData[8*i+1]) && coords.Z == VertexData[8*i+2]) return i;
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

    Debug_Log(glGetUniformLocation(m_GLProgramID, "tex0"));

    glUniform1i(glGetUniformLocation(m_GLProgramID, "tex0"), 0);
}

Shader* drn::CurrentShader{&DefaultShader};


//-------------//
// Image Class //
//-------------//

Image::Image(char* ImageName, std::vector<SpriteCoords> imgCoords) {
    m_imgData = stbi_load(ImageName, &m_Width, &m_Height, &m_nrChannels, 0);

    if (!m_imgData) {
        Debug_Error("Image " << ImageName << " not found");
        throw std::runtime_error("Image Not Found");
    }

    if (imgCoords[0].w == 0 && imgCoords[0].h == 0) {
        //Debug_Warn("Unable to generate sprite coordinates. Creating generic texture coords");
        m_imgCoords = {{0, 0, m_Width, m_Height}};
    } else {
        m_imgCoords = imgCoords;
    }
}

void Image::Init(GLenum slot) {
    // Generating GL Components. Normal Repeat, MAG filter is nearest, and MIN filter is linear. 
    glGenTextures(1, &m_glTexture);

    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, m_glTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imgData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(m_imgData);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Image::UseImage(GLenum slot) {
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, m_glTexture);
}

Image::~Image() {
    //stbi_image_free(m_imgData);
}

//-------------------//
// Drawing Functions //
//-------------------//


void drn::DrawRect(Vec2<float> pos, Vec2<float> size) {
    drn::DrawQuad(pos, {pos.X, pos.Y+size.Y}, {pos.X+size.X, pos.Y}, pos+size);
}

void drn::DrawQuad(Vec2<float> a, Vec2<float> b, Vec2<float> c, Vec2<float> d) {
    drn::DrawPlane({a.X, a.Y, 1.f}, {b.X, b.Y, 1.f}, {c.X, c.Y, 1.f}, {d.X, d.Y, 1.f});
}

// Roberto: [REDO] Needs a Heavy Rework.
// The Planes assume that the vertex color and UV are the same for every usage of the point.
// This creates clashing between UV points possibly leading to sprites that are L*0 u^2.
// There may be similar situations for RGB values too
void drn::DrawPlane(Vec3<float> a, Vec3<float> b, Vec3<float> c, Vec3<float> d) {
    // Setting up Vertex and Index Data

    // X, Y, Z, Vertex R, Vertex G, Vertex B
    GLfloat GeneratedVertexData[] = {
        (a.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-a.Y*2/WindowPT->GetWindowDimensions().Y)+1.f, a.Z/120, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        (b.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-b.Y*2/WindowPT->GetWindowDimensions().Y)+1.f, b.Z/120, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        (c.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-c.Y*2/WindowPT->GetWindowDimensions().Y)+1.f, c.Z/120, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        (d.X*2/WindowPT->GetWindowDimensions().X)-1.f, (-d.Y*2/WindowPT->GetWindowDimensions().Y)+1.f, d.Z/120, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };

    int indexOrder[] = {0, 1, 2, 3, 2, 1};

    // This makes sure vertex positions are not reused
    for (int i = 0; i < 6; i++) {
        int VertexExists{FindVertex({GeneratedVertexData[8*indexOrder[i]], GeneratedVertexData[8*indexOrder[i]+1], GeneratedVertexData[8*indexOrder[i]+2]})};
        if (VertexExists != -1) {
            indexData.push_back(VertexExists);
            continue;
        }

        indexData.push_back(vertexCounter++);
        
        // Push New Vertices
        
        // ROBERTO: is there a more practical way to push the vertex data?
        VertexData.push_back(GeneratedVertexData[8*indexOrder[i]]);
        VertexData.push_back(GeneratedVertexData[8*indexOrder[i]+1]);
        VertexData.push_back(GeneratedVertexData[8*indexOrder[i]+2]);
        VertexData.push_back(GeneratedVertexData[8*indexOrder[i]+3]);
        VertexData.push_back(GeneratedVertexData[8*indexOrder[i]+4]);
        VertexData.push_back(GeneratedVertexData[8*indexOrder[i]+5]);
        VertexData.push_back(GeneratedVertexData[8*indexOrder[i]+6]);
        VertexData.push_back(GeneratedVertexData[8*indexOrder[i]+7]);
    }
}

void drn::DrawCube(Vec3<float> p, Vec3<float> s, Vec3<float> r) {
    Vec3<float> cv[8] = {
        ((Vec3<float>){-s.X/2, -s.Y/2, -s.Z/2}).rotate(r)+p,
        ((Vec3<float>){-s.X/2, -s.Y/2, s.Z/2}).rotate(r)+p,
        ((Vec3<float>){-s.X/2, s.Y/2, -s.Z/2}).rotate(r)+p,
        ((Vec3<float>){-s.X/2, s.Y/2, s.Z/2}).rotate(r)+p,
        ((Vec3<float>){s.X/2, -s.Y/2, -s.Z/2}).rotate(r)+p,
        ((Vec3<float>){s.X/2, -s.Y/2, s.Z/2}).rotate(r)+p,
        ((Vec3<float>){s.X/2, s.Y/2, -s.Z/2}).rotate(r)+p,
        ((Vec3<float>){s.X/2, s.Y/2, s.Z/2}).rotate(r)+p
    };

    DrawPlane(cv[0], cv[1], cv[3], cv[2]);
    DrawPlane(cv[4], cv[5], cv[7], cv[6]);
    DrawPlane(cv[3], cv[4], cv[2], cv[7]);
    DrawPlane(cv[0], cv[3], cv[5], cv[4]);
    DrawPlane(cv[0], cv[3], cv[4], cv[6]);
    DrawPlane(cv[0], cv[3], cv[5], cv[4]);
}

void drn::DrawCube(Vec3<float> pos, Vec3<float> size) {
    drn::DrawCube(pos, size, {0, 0, 0});
}