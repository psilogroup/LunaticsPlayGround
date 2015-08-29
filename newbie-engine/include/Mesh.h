#ifndef __MESH__
#define __MESH__

#ifdef WIN32
#include <windows.h>
#endif

#include "vec3d.h"
#include "Object.h"
#include "Graphics.h"
#include "TexCoord2.h"
#include "TexturePCX.h"
#include "VertexBufferObject.h"
#include "BZK_ParsingTools.h"
#include <ode/ode.h>
#include <string>
#include <iostream>

class Mesh:public Object
{

 public:
   Mesh();
   Mesh(std::string filepath);
   virtual void MakeBody(dWorldID world);
   virtual void MakeGeom(dSpaceID space);
   virtual void Draw();
   virtual void Update();

   ~Mesh();

   int numElements;

   vec3d *vecs;
   dTriMeshDataID triData;
   GLint listId;
   dTriIndex *indexs;
    TexCoord2 *texCoord;
    TexturePCX *texture;
   int numVecs;
   int numTrigs;
   int numIndexs;
   int numTexs;
   ifstream Datafile;
};

#endif
