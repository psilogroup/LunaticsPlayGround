#ifndef __CUBE__
#define __CUBE__
#include "Object.h"
#include "Texture.h"
class Cube:public Object
{
public:
    Cube();
    Cube(bool useVbo);
    virtual void Draw();
    virtual void Update();
    vec3d *vecs;
    dTriMeshDataID triData;
    dTriIndex *indexs;
    TexCoord2 *texCoord;
    int numVecs;
    int numTrigs;
    int numIndexs;
    int numTexs;
    bool useVBO;

    virtual ~Cube();
};
#endif
