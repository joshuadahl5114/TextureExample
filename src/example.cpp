
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "platform.hpp"

#include "example.h"
#include "glslshader.h"


Example::Example()
{
    std::vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("basic-fixed.vert"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("basic-fixed.frag"), GL_FRAGMENT_SHADER));
    m_program = new tdogl::Program(shaders);
    
    m_terrain.SetProgram(m_program);
    
    //m_GLSLProgram = new GLSLProgram("data/basic-fixed.vert", "data/basic-fixed.frag");
}

Example::~Example() 
{
    delete m_program;
    //delete m_GLSLProgram;
}

bool Example::init()
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    
    //using TDOGLs GLSL programming
    //if (!m_GLSLProgram->initialize())
    //{
       // std::cerr << "Could not initialize the shaders" << std::endl;
       // return false;
    //}

    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.5f, 0.9f, 0.5f);

    if (!m_terrain.loadHeightmap("data/heightmap.raw", 65)) 
    {
        std::cerr << "Could not load the terrain" << std::endl;
        return false;
    }

    //Bind the attribute locations
	//m_GLSLProgram->bindAttrib(0, "a_Vertex");
	//m_GLSLProgram->bindAttrib(1, "a_Color");
    //m_GLSLProgram->bindAttrib(2, "a_TexCoord");
	
	//Re link the program
	//m_GLSLProgram->linkProgram();
	
	//m_GLSLProgram->bindShader(); //Enable our shader
    
    if (!m_grassTexture.load("data/grass.tga"))
    {
        std::cerr << "Could not load the grass texture" << std::endl;
        return false;
    }

    
    glGenTextures(1, &m_grassTexID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_grassTexID);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0, GL_RGB8, m_grassTexture.getWidth(), 
                      m_grassTexture.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 
                      m_grassTexture.getImageData());
    glBindTexture(GL_TEXTURE_2D, 0);
     
    
    this->m_terrain.SetTextureHandle(m_grassTexID);
    
    /*gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, m_grassTexture.getWidth(), 
                      m_grassTexture.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, 
                      m_grassTexture.getImageData());*/

    //glEnableVertexAttribArray(0); //Enable the vertex attribute
    //glEnableVertexAttribArray(1); //Enable the color attribute
    //glEnableVertexAttribArray(2); //Enable the texture coordinate attribute

    //Return success
    return true;
}



void Example::prepare(float dt)
{

}

void Example::render(tdogl::Camera camera)
{
    float modelviewMatrix[16];
    //float projectionMatrix[16];
    
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Load the identity matrix (reset to the default position and orientation)
    
    //uncomment for wireframe mode
   // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    m_program->use();
    
    //glLoadIdentity();

    //eventually use the GLM library to construct the matrix
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -20.0f, 0.0f));
    //glm::mat4 projectionMatrix = glm::perspective(glm::radians(52.0f), 4.0f/3.0f, 1.0f, 100.0f);
    //glTranslatef(0.0f, -20.0f, 0.0f);
    //glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
    //Translate using our zPosition variable
    //glTranslatef(0.0, 0.0, -50.0f);

    //Get the current matrices from OpenGL
    //glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    //glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);

    float model[16] = { 1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f };
    float project[16] = {0,4.24,0,0,0,0,0,-1,0,78.02,0,0,0,0,0,0};
    
    glm::mat4 ident;
    
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -20.0f, 0.0f));
    
    //glm::mat4 projectionMatrix = glm::perspective(glm::radians(50.0f), 4.0f/3.0f, .01f, 100.0f);
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(50.0f), 4.0f/3.0f, .01f, 100.0f);
    
    m_program->setUniform("camera", camera.matrix());
    //m_program->setUniformMatrix4("modelview_matrix",model);
    m_program->setUniform("modelview_matrix", glm::rotate(translate, glm::radians(0.75f), glm::vec3(0,1,0)));
    
    m_program->setUniform("texture0", 0);
    
    
    //what is causing problems, more than likely its in here
     m_terrain.render();
    
    m_program->stopUsing();

}

tdogl::Program* Example::GetProgram()
{
    return this->m_program;
}

void Example::shutdown()
{

}

void Example::bindVertextArray()
{
    m_terrain.bindVertextArray();
}

void Example::onResize(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //fix this later
    //gluPerspective(52.0f, float(width) / float(height), 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
