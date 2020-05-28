#ifndef __CUBE__
#define __CUBE__
#include "Object.h"
#include "Texture.h"
#include "Mesh.h"
class Cube:public Object
{
public:
    Cube();
   
    virtual void Draw();
    virtual void Update();
    virtual void SetTexture(Texture* tex);
    vec3d *vecs;
    dTriMeshDataID triData;
    dTriIndex *indexs;
    TexCoord2 *texCoord;
    Mesh* mesh;
    int numVecs;
    int numTrigs;
    int numIndexs;
    int numTexs;
    bool useVBO;

    virtual ~Cube();
};
#endif
