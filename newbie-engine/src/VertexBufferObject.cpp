#include "VertexBufferObject.h"
#include <Windows.h>
#include <GL/glew.h>

VertexBufferObject::VertexBufferObject()
{
    vertexBuffId = 0;
    indexBuffId = 0;
    normalBuffId = 0;
    texBuffId = 0;
    numIndices = 0;
    vertices = NULL;
    indexs = NULL;
    normals = NULL;
    texCoord = NULL;
    glMode = 0;

}

void VertexBufferObject::setVertices(vec3d *data,unsigned int size)
{


    glGenBuffers( 1, &vertexBuffId);
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffId );

    vertices = data;
    numIndices = size;

	glBufferDataARB( GL_ARRAY_BUFFER, size * 3 * sizeof(float), data, GL_STATIC_DRAW_ARB );

}
void VertexBufferObject::setIndexs(unsigned int *data,unsigned int size)
{
    glGenBuffers( 1, &indexBuffId );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffId );

    indexs = data;

    numIndices = size;
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER, size*sizeof(unsigned int), data, GL_STATIC_DRAW_ARB );
}

void VertexBufferObject::setNormals(float *data,unsigned int size)
{
}

void VertexBufferObject::setTexCoords(TexCoord2 *data,unsigned int size)
{
    glGenBuffers( 1, &texBuffId );
	glBindBuffer( GL_ARRAY_BUFFER, texBuffId );

    texCoord = data;
	glBufferDataARB( GL_ARRAY_BUFFER, size * 2 * sizeof(float), data, GL_STATIC_DRAW_ARB );
}

void VertexBufferObject::draw()
{

    if (vertexBuffId != 0 )
    {

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffId);
        glVertexPointer(3,GL_FLOAT,0,0);
        glEnableClientState(GL_VERTEX_ARRAY);

    }

     if (indexBuffId != 0 )
    {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffId);
        glIndexPointer(GL_UNSIGNED_INT,0,0);
        glEnableClientState(GL_INDEX_ARRAY);

    }



    if (texBuffId != 0)
    {

        glBindBuffer(GL_ARRAY_BUFFER, texBuffId);
        glTexCoordPointer(2,GL_FLOAT,0,0);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    }

    glDrawArrays(glMode,0,numIndices);
    //glDrawElements(glMode,numIndices,GL_UNSIGNED_INT,0);



    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

VertexBufferObject::~VertexBufferObject()
{

}