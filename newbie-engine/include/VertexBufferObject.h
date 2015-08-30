#ifndef __VBO__
#define __VBO__

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>
#include "vec3d.h"
#include "TexCoord2.h"

/**
* @brief Gera Buffer Object
**/

class VertexBufferObject
{
    public:
        unsigned int vertexBuffId; //id do buffer vertices
        unsigned int indexBuffId; //id do buffer indices
        unsigned int normalBuffId; //id do buffer de normal
        unsigned int texBuffId; //id do buffer de coordenada de textura
        unsigned int numIndices;
        void *vertices; // data dos vertices
        void *indexs; // data dos indicex
        float *normals; // data das normais
        void *texCoord; //data das coordenadas de Texturas
        int glMode; //GL_
        VertexBufferObject();

        /**
        * @brief seta os vetices do VBO
        * @param vec3d *data ponteiro para os vertices
        * @param uint32 size tamanho do buffer
        */
        void setVertices(void *data,unsigned int size);

        /**
        * @brief seta os indices do VBO
        * @param uint32 *data ponteiro para os indices
        * @param uint32 size tamanho do buffer
        */
        void setIndexs(void*data,unsigned int size);

        /**
        * @brief seta as normais do VBO
        * @param vec3d *data ponteiro para os normais
        * @param uint32 size tamanho do buffer
        */
        void setNormals(float *data,unsigned int size);

        /**
        * @brief seta as coordenadas de textura VBO
        * @param TexCoord2 *data ponteiro para os vertices
        * @param uint32 size tamanho do buffer
        */
        void setTexCoords(void *data,unsigned int size);

        /**
        * @brief desenha o VBO
        */
        void draw();
        virtual ~VertexBufferObject();
};
#endif
