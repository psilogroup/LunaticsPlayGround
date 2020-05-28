#include "Cube.h"
#include "VertexBufferObject.h"
#include <math.h>

Cube::Cube()
{

    iSize.x = iSize.y = iSize.z = 1;
    iPosition.x = iPosition.y = iPosition.z = 0;
    iVel.x = iVel.y =iVel.z = 0;
    iRotate.x = iRotate.y = iRotate.z = 0.0f;
    iM = 1;
    Mat = new Material();
    dQFromAxisAndAngle(q,1,0,0,M_PI*0.5);

    data = new BodyData();
    data->setName("Cube");

    mesh = new Mesh("storage\\models\\cube.obj");
   
}



void Cube::Draw()
{
    float lx = iSize.x*0.5f;
    float ly = iSize.y*0.5f;
    float lz = iSize.z*0.5f;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Transform();
    glScalef(iSize.x,iSize.y,iSize.z);

   
	if (Mat != NULL) {
		Mat->Build();

	}

    mesh->Draw();
   // glutSolidCube(1.0);
    

    glPopMatrix();

}

void Cube::Update()
{
    const dReal *p,*r;
    UpdateDisableState();
    p = dGeomGetPosition(iGeom);
    iPosition.x = p[0];
    iPosition.y = p[1];
    iPosition.z = p[2];
   // dBodyEnable(iBody);
}

void Cube::SetTexture(Texture* tex)
{
    if (mesh != NULL)
        mesh->texture = tex;
}

Cube::~Cube()
{

}
