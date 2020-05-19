#include "BZK_ParsingTools.h"
#include "Wavefront.h"
#include "Graphics.h"
#include "baselib.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

Wavefront::Wavefront(string filename)
{

    iSize.x = iSize.y = iSize.z = 1;
    iPosition.x = iPosition.y = iPosition.z = 0;
    iVel.x = iVel.y = iVel.z = 0;
    //   dMassSetZero(&iMass);
    iM = 1;
    cout << "Lendo Modelo " << filename << endl;
    load(filename);
}

Wavefront::Wavefront()
{

    iSize.x = iSize.y = iSize.z = 1;
    iPosition.x = iPosition.y = iPosition.z = 0;
    iVel.x = iVel.y = iVel.z = 0;
    iM = 1;

}

void Wavefront::load(string filename)
{
    cout << "Lendo Modelo " << filename << endl;
    string echo;
    ifstream datafile;
    numVecs = 0;
    numTrigs = 0;
    numIndexs = 0;
    int nVecs = 0;
    int nIndexs = 0;
    datafile.open(filename.c_str());
   
    while (!datafile.eof())
    {
        echo = BZK_ParsingTools::GetNextToken(&datafile);

        if (echo == "v")
            numVecs++;

        if (echo == "f")
            numIndexs += 3;
    }

    datafile.clear();

    datafile.open(filename.c_str());
    ifstream data2;
    data2.open(filename.c_str());
    //     vecs=new dVector3[numVecs+1];
    indexs = (dTriIndex*)malloc(sizeof(dTriIndex) * numIndexs + 1);

    while (!data2.eof())
    {
        echo = BZK_ParsingTools::GetNextToken(&data2);
        if (echo == "v")
        {
            vecs[nVecs].x = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&data2));
            vecs[nVecs].y = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&data2));
            vecs[nVecs].z = BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&data2));
            nVecs++;
        }

        if (echo == "f")
        {
            indexs[nIndexs] = (int)BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&data2)) - 1;
            nIndexs++;
            indexs[nIndexs] = (int)BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&data2)) - 1;
            nIndexs++;
            indexs[nIndexs] = (int)BZK_ParsingTools::GetNumber(BZK_ParsingTools::GetNextToken(&data2)) - 1;
            nIndexs++;
        }

    }
    datafile.clear();
}


Wavefront::~Wavefront()
{

}
