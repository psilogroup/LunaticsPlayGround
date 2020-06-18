#ifndef __CUBE__
#define __CUBE__
#include "Object.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "baselib.h"
class Cube:public Object
{
public:
    Cube();
   
    virtual void Draw(Shader* shader);
    virtual void Update();
    virtual void SetTexture(Texture* tex);
    virtual glm::mat4 GetModelMatrix();
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
