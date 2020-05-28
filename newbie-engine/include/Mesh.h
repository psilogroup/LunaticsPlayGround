#ifndef __MESH__
#define __MESH__

#ifdef WIN32
#include <windows.h>
#endif

#include "vec3d.h"
#include "Graphics.h"
#include "TexCoord2.h"
#include "Texture.h"
#include "VertexBufferObject.h"
#include "BZK_ParsingTools.h"
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

    int numElements;

    vec3d *vecs;
    vec3d* normals;
    dTriIndex *indexs;
    TexCoord2 *texCoord;
    Texture *texture;
    int numVecs;
    int numTrigs;
    int numIndexs;
    int numTexs;
    int numNormals;
    VertexBufferObject* vbo;
    
};

#endif
