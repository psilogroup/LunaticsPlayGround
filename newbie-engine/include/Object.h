#ifndef __OBJECT_C__
#define __OBJECT_C__

#ifdef WIN32
#include <windows.h>
#endif

#include <ode/ode.h>
#include "vec3d.h"
#include "Material.h"
#include "definitions.h"
#include "BZK_List.h"
#include "VertexBufferObject.h"
#include "Texture.h"
#include "glsl.h"
# include <iostream>
# include <fstream>
#include <string>
#include <sstream>

class BodyData
{
    private:
        std::string name;

    public:
    void setName(std::string _name) {name = _name;};
    std::string getName(){return name;};
};

class Object
{
public:
    Object();
    virtual void MakeBody(dWorldID world);
    virtual void MakeGeom(dSpaceID space);
    virtual void LinkBodyWithGeom();
    virtual void Update();
    virtual void UpdateDisableState();
    virtual void Draw();

    virtual void showAABB();
    void setRotation(float x,float y,float z);
    void setPosition(float x,float y,float z);
    void Transform();

    //cwc::glShader *shader;
    Material *Mat;
    vec3d iPosition;
    vec3d iSize;
    vec3d iRotate;
    vec3d iVel;
    dQuaternion q;
    float iM;
    float disabledSteps;
    dMass iMass;
    dBodyID iBody;
    dGeomID iGeom;
    VertexBufferObject *vbo;
    Texture *texture;
    BodyData *data;
    virtual ~Object();

};
#endif
