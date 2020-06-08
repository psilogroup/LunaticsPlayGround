#pragma once

#include "vec3d.h"
#include "TexCoord2.h"

typedef struct VertexData
{
    vec3d vector;
    vec3d normal;
    TexCoord2 texCoord;
};
