#include <drn/graphics.hpp>

#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <exception>
#include <iostream>

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
    "   vec4 Color = texture(tex0, FragTexCoord);\n"
    "   FragColor = vec4(vec3(1-gl_FragCoord.z)*Color.xyz, 1.0f);\n"
    //"   FragColor = vec4(FragTexCoord.xy, 0.0f, 1.0f);"
    "}\n"
};

extern std::vector<GLfloat> VertexData;
extern std::vector<GLuint> indexData;
extern std::vector<GLfloat> normalMaps;
extern std::vector<GLfloat> textureCoords;

extern int vertexCounter;
int vertexCounter{0};

// To make comparing and vertex storage a lot easier
struct Vertex {
    float X;
    float Y;
    float Z;
    float R;
    float G;
    float B;
    float U;
    float V;

    bool operator==(Vertex a) {
        if (X != a.X) return false;
        if (Y != a.Y) return false;
        if (Z != a.Z) return false;
        if (R != a.R) return false;
        if (G != a.G) return false;
        if (B != a.B) return false;
        if (U != a.U) return false;
        if (V != a.V) return false;

        return true;
    };
};

int FindVertex(Vertex coords) {
    if (VertexData.size() == 0) return -1;

    for (int i = 0; i < VertexData.size()/8; i++) {
        Vertex testvertex{VertexData[8*i], VertexData[8*i+1], VertexData[8*i+2], VertexData[8*i+3], VertexData[8*i+4], VertexData[8*i+5], VertexData[8*i+6], VertexData[8*i+7]};
        if (coords == testvertex) return i;
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

void Image::Init() {
    // Generating GL Components. Normal Repeat, MAG filter is nearest, and MIN filter is linear. 
    glGenTextures(1, &m_glTexture);
    glBindTexture(GL_TEXTURE_2D, m_glTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imgData);
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

void drn::DrawPlane(Vec3<float> a, Vec3<float> b, Vec3<float> c, Vec3<float> d) {
    // Setting up Vertex and Index Data

    // X, Y, Z, Vertex R, Vertex G, Vertex B
    Vertex GeneratedVertexData[] = {
        {a.X/WindowPT->GetWindowDimensions().X*2, -a.Y/WindowPT->GetWindowDimensions().Y*2, a.Z/120, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {b.X/WindowPT->GetWindowDimensions().X*2, -b.Y/WindowPT->GetWindowDimensions().Y*2, b.Z/120, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        {c.X/WindowPT->GetWindowDimensions().X*2, -c.Y/WindowPT->GetWindowDimensions().Y*2, c.Z/120, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},
        {d.X/WindowPT->GetWindowDimensions().X*2, -d.Y/WindowPT->GetWindowDimensions().Y*2, d.Z/120, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}
    };

    int indexOrder[] = {0, 1, 2, 3, 2, 1};

    // This makes sure vertex positions are not reused
    for (int i = 0; i < 6; i++) {
        int VertexExists{FindVertex(GeneratedVertexData[indexOrder[i]])};
        if (VertexExists != -1) {
            indexData.push_back(VertexExists);
            continue;
        }

        indexData.push_back(vertexCounter++);
        
        // Push New Vertices
        
        // ROBERTO: is there a more practical way to push the vertex data?
        VertexData.push_back(GeneratedVertexData[indexOrder[i]].X);
        VertexData.push_back(GeneratedVertexData[indexOrder[i]].Y);
        VertexData.push_back(GeneratedVertexData[indexOrder[i]].Z);
        VertexData.push_back(GeneratedVertexData[indexOrder[i]].R);
        VertexData.push_back(GeneratedVertexData[indexOrder[i]].G);
        VertexData.push_back(GeneratedVertexData[indexOrder[i]].B);
        VertexData.push_back(GeneratedVertexData[indexOrder[i]].U);
        VertexData.push_back(GeneratedVertexData[indexOrder[i]].V);
    }
}

void drn::DrawCube(Vec3<float> p, Vec3<float> s, Vec3<float> r) {
    Vec3<float> cv[8] = {
        ((Vec3<float>){-s.X/2, -s.Y/2, -s.Z/2}).rotate(r)+p, // -1 -1 -1
        ((Vec3<float>){-s.X/2, -s.Y/2, s.Z/2}).rotate(r)+p,  // -1 -1 1
        ((Vec3<float>){-s.X/2, s.Y/2, -s.Z/2}).rotate(r)+p,  // -1 1 -1
        ((Vec3<float>){-s.X/2, s.Y/2, s.Z/2}).rotate(r)+p,   // -1 1 1
        ((Vec3<float>){s.X/2, -s.Y/2, -s.Z/2}).rotate(r)+p,  // 1 -1 -1
        ((Vec3<float>){s.X/2, -s.Y/2, s.Z/2}).rotate(r)+p,   // 1 -1 1
        ((Vec3<float>){s.X/2, s.Y/2, -s.Z/2}).rotate(r)+p,   // 1 1 -1
        ((Vec3<float>){s.X/2, s.Y/2, s.Z/2}).rotate(r)+p     // 1 1 1
    };

    DrawPlane(cv[0], cv[2], cv[4], cv[6]);
    DrawPlane(cv[0], cv[4], cv[1], cv[5]);
    DrawPlane(cv[4], cv[6], cv[5], cv[7]);
    DrawPlane(cv[0], cv[1], cv[2], cv[3]);
    DrawPlane(cv[2], cv[3], cv[6], cv[7]);
    DrawPlane(cv[1], cv[5], cv[3], cv[7]);
}

void drn::DrawCube(Vec3<float> pos, Vec3<float> size) {
    drn::DrawCube(pos, size, {0, 0, 0});
}