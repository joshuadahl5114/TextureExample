#ifndef _EXAMPLE_H
#define _EXAMPLE_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <vector>
#include <string>
#include "terrain.h"
#include "targa.h"

#include "tdogl/Program.h"
#include "tdogl/Camera.h"

class GLSLProgram;

using std::vector;
using std::string;

class Example 
{
public:
    Example();
    virtual ~Example();

    bool init();
    void prepare(float dt);
    void render(tdogl::Camera camera);
    void shutdown();
    void bindVertextArray();
    void LoadShaders();
    tdogl::Program* GetProgram();
    
    void onResize(int width, int height);

private:
    Terrain m_terrain;
    GLSLProgram* m_GLSLProgram;
    TargaImage m_grassTexture;
    GLuint m_grassTexID;
    GLuint m_VAO;
    tdogl::Program* m_program;
};

#endif
