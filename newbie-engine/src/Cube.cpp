#include "Cube.h"
#include "VertexBufferObject.h"
#include "baselib.h"
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



void Cube::Draw(Shader *shader)
{
    float lx = iSize.x*0.5f;
    float ly = iSize.y*0.5f;
    float lz = iSize.z*0.5f;

    
    glm::mat4 model = this->GetModelMatrix();
    shader->SetMat4("u_model", glm::value_ptr(model));

    mesh->Draw();
   // glutSolidCube(1.0);
    
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

glm::mat4 Cube::GetModelMatrix()
{
    const float* pos = dGeomGetPosition(iGeom);
    const float* R = dGeomGetRotation(iGeom);

    glm::mat4 m1 = glm::mat4(1.0f);

    float* matrix = glm::value_ptr(m1);
    matrix[0] = R[0];
    matrix[1] = R[4];
    matrix[2] = R[8];
    matrix[3] = 0;
    matrix[4] = R[1];
    matrix[5] = R[5];
    matrix[6] = R[9];
    matrix[7] = 0;
    matrix[8] = R[2];
    matrix[9] = R[6];
    matrix[10] = R[10];
    matrix[11] = 0;
    matrix[12] = pos[0];
    matrix[13] = pos[1];
    matrix[14] = pos[2];
    matrix[15] = 1;

    glm::mat4 model = glm::scale(m1, glm::vec3{ iSize.x,iSize.y,iSize.z });

    return model;
}

Cube::~Cube()
{

}
