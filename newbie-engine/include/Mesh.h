#ifndef __MESH__
#define __MESH__

#ifdef WIN32
#include <windows.h>
#endif

#include "vec3d.h"
#include "Graphics.h"
#include "TexCoord2.h"
#include "Texture.h"
#include "VertexData.h"
#include "VertexBufferObject.h"
#include "BZK_ParsingTools.h"
#include "Shader.h"
#include "baselib.h"
#include <string>
#include <iostream>



class Mesh
{

public:
    Mesh();
    Mesh(std::string filepath);
    virtual void Draw();
    ~Mesh();

   
    Texture *texture;
    int numVecs;
    int numIndexs;
    
private:
    unsigned int VBO, VAO;
    
};

#endif
