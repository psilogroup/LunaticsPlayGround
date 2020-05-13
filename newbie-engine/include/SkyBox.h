#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/gl.h>
#include "Texture.h"
#include "vec3d.h"

#include <string.h>

/** \brief
 * Classe para desenho de SkyBox
 */
class SkyBox
{
public:

    SkyBox(){};
    SkyBox (const char *f,const char *b,const char *l,const char *r,const char *u);

    void SetPosition(vec3d pos);
    void SetSize(float sz);
    void Draw(vec3d angles);

    Texture *front;
    Texture *back;
    Texture *left;
    Texture *right;
    Texture *Up;

    vec3d Position;
    float Size;

    virtual ~SkyBox();
protected:
private:
};

#endif // SKYBOX_H
