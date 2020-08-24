#ifndef BOGLGP_TERRAIN_H
#define BOGLGP_TERRAIN_H

#include <GL/Glew.h>
#include "tdogl/Program.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Vertex 
{
    float x, y, z;
    Vertex(float x, float y, float z) 
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct TexCoord
{
    float s, t;
    TexCoord(float s, float t)
    {
        this->s = s;
        this->t = t;
    }
};

struct Color 
{
    float r, g, b;
    Color(float r, float g, float b) 
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

class Terrain 
{
public:
    Terrain();
    Terrain(tdogl::Program* program);
    bool loadHeightmap(const string& rawFile, int width);
    void render();
    void bindVertextArray();
    void SetProgram(tdogl::Program* program);
    void SetTextureHandle(GLuint handle);
    
private:
    void generateVertices(const vector<float> heights, int width);
    void generateIndices(int width);
    void generateTexCoords(int width);
    
    
    
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    GLuint m_colorBuffer;
    GLuint m_texCoordBuffer;
    
    tdogl::Program* m_program;
    
    GLuint m_VAO;
    GLuint m_grassTexID;
    
    vector<Vertex> m_vertices;
    vector<Color> m_colors;
    vector<TexCoord> m_texCoords;
    
    vector<GLfloat> m_verts;
    vector<GLfloat> m_colrs;
    vector<GLfloat> m_texs;
    
    vector<GLuint> m_indices;
};

#endif
