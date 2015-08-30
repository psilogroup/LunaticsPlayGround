#include "Texture.h"
#include <string.h>
#include <SDL2/SDL_image.h>
//static int texCount = 1;
/**
 * @param  filename Load a Texteture
 */
Texture::Texture (const char * filename )
{
    id = 0;
    image = IMG_Load(filename);

    if (image)
    {
        GLenum texture_format;
        GLint  nOfColors;
        unsigned int size = sizeof(image->pixels);
        nOfColors = image->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
            if (image->format->Rmask == 0x000000ff)
                texture_format = GL_RGBA;
            else
                texture_format = GL_BGRA;
        }
        else if (nOfColors == 3)       // no alpha channel
        {
            if (image->format->Rmask == 0x000000ff)
                texture_format = GL_RGB;
            else
                texture_format = GL_BGR;
        }
        else
        {
            printf("warning: the image is not truecolor..  this will probably break\n");
            // this error should not go unhandled
        }
        glGenTextures(1, &name);

        id = name;
        glBindTexture(GL_TEXTURE_2D, name);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST); // The magnification function ("linear" produces better results)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function


        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, image->w, image->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, image->pixels );

        gluBuild2DMipmaps (GL_TEXTURE_2D, nOfColors, image->w, image->h,
                           texture_format, GL_UNSIGNED_BYTE, image->pixels);



        glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    }

}



void Texture::bind ()
{
    try
    {
        glEnable(GL_TEXTURE);
        glEnable(GL_TEXTURE_2D);
        if (&name !=NULL && &name > 0)
        {
            glBindTexture(GL_TEXTURE_2D,name);
        }
    }
    catch (char *e)
    {

    }
}




void Texture::end()

{
    glDisable(GL_TEXTURE);
    glDisable(GL_TEXTURE_2D);

}

Texture::~Texture()
{
    if (&name != NULL && &name > 0)
        glDeleteTextures(1,&name);

    SDL_FreeSurface(image);

}
