#include "BZK_ParsingTools.h"
#include "Mesh.h"
#include "Graphics.h"
#include "BZK_List.h"

Mesh::Mesh()
{
    iSize.x = iSize.y = iSize.z = 1;
    iPosition.x = iPosition.y = iPosition.z = 0;
    iVel.x = iVel.y =iVel.z = 0;

    iM = 1;

    Mat = new Material();
    setColor(Mat->Ka,0.0,0.0,0.0);
    setColor(Mat->Kd,0.0,0.0,0.0);
    setColor(Mat->Ks,1.0,1.0,1.0);
}


Mesh::Mesh(std::string filepath)
{
    iSize.x = iSize.y = iSize.z = 1;
    iPosition.x = iPosition.y = iPosition.z = 0;
    iVel.x = iVel.y =iVel.z = 0;
    //   dMassSetZero(&iMass);
    iM = 1;

    Mat = new Material();
    setColor(Mat->Ka,0.0,0.0,0.0);
    setColor(Mat->Kd,0.0,0.0,0.0);
    setColor(Mat->Ks,1.0,1.0,1.0);

    Datafile.clear();
    Datafile.open(filepath.c_str());
    BZK_List  <vec3d> vList;
    BZK_List <TexCoord2> tList;

    numVecs = 0;
    numTexs = 0;

    while (!Datafile.eof())
    {
        std::string  Echo=BZK_ParsingTools::GetNextToken(&Datafile);

        if (Echo == "v:")
        {
            vec3d v;
            v.x = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
            v.y = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
            v.z = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
            vList.Add(v);
            numVecs++;
        }

        if (Echo == "tex:")
        {
            texture = new Texture(BZK_ParsingTools::GetNextToken(&Datafile).c_str());
        }

        if (Echo == "t:")
        {
            TexCoord2 coord;
            coord.u = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));
            coord.v = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&Datafile));

            tList.Add(coord);
            numTexs++;
        }

    }

    std::cout << numVecs;
    vecs = new vec3d[numVecs];
    numIndexs = numVecs;
    indexs = new dTriIndex[numIndexs];


    for (int i =0; i < vList.TotalItems(); i++)
    {
        vecs[i] = vList[i];
        indexs[i] = i;
    }

    if (numTexs > 0)
    {
        texCoord = new TexCoord2[numTexs];

        for (int i=0; i<tList.TotalItems(); i++)
        {
            texCoord[i] = tList[i];
        }
    }

    Datafile.clear();

    vbo = new VertexBufferObject();
    vbo->glMode = GL_TRIANGLES;

    vbo->setVertices(vecs,numVecs);
    vbo->setIndexs(indexs,numIndexs);

    if (numTexs > 0)
    {
        vbo->setTexCoords(texCoord,numTexs);
    }


}
void Mesh::MakeBody(dWorldID world)
{

    iBody = dBodyCreate(world);
    dGeomSetBody(iGeom,iBody);
    dMassSetZero(&iMass);
    dMassSetTrimesh(&iMass,iM,iGeom);
    dMassTranslate( &iMass, -iMass.c[0], -iMass.c[1], -iMass.c[2] );
    dBodySetMass(iBody,&iMass);

}

void Mesh::MakeGeom(dSpaceID space)
{

    triData = dGeomTriMeshDataCreate();
    dGeomTriMeshDataBuildSimple(triData, (dReal*)vecs, numVecs,(dTriIndex*)indexs, numIndexs);
    iGeom = dCreateTriMesh(space, triData,0,0,0);

    dMatrix3 R,R0,R1,R2,R3;

    dRFromAxisAndAngle(R1,1,0,0,DEG2RAD(iRotate.x));
    dRFromAxisAndAngle(R2,0,1,0,DEG2RAD(iRotate.y));
    dRFromAxisAndAngle(R3,0,0,1,DEG2RAD(iRotate.z));
    dMultiply0 (R0,R1,R2,3,3,3);
    dMultiply0 (R, R0,R3,3,3,3);
    dGeomSetRotation(iGeom,R);
    // dGeomSetQuaternion(iGeom,q);
    dGeomSetPosition(iGeom, iPosition.x, iPosition.y, iPosition.z);
    //dMassTranslate(&iMass,-iPosition.x, -iPosition.y, -iPosition.z);
}

void Mesh::Draw()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();


    glTranslatef(iPosition.x,iPosition.y,iPosition.z);
    glScalef(3,3,3);
    if (Mat != NULL)
    {
        Mat->Build();

    }
    //Draw Here
    if (texture != NULL)
    {
        texture->bind();
    }

    ;

    vbo->draw();




    if (texture != NULL)
    {
        texture->end();
    }
    glPopMatrix();

}

void Mesh::Update()
{
    const dReal *p = dGeomGetPosition(iGeom);
    iPosition.x = p[0];
    iPosition.y = p[1];
    iPosition.z = p[2];
};

Mesh::~Mesh()
{
}
