/*
 * TexturePCX.h
 *
 *  Created on: 11/04/2009
 *      Author: newbie
 */

#ifndef TEXTUREPCX_H_
#define TEXTUREPCX_H_

#include "Texture.h"
class TexturePCX : Texture{
public:
	TexturePCX(){};
	TexturePCX(const char *filename);
	/**
	 * bind the texture
	 */
	void bind ();
	void begin();
	void end();
	virtual ~TexturePCX();
	SDL_Surface* image;
	GLuint name;
	int id;
};

#endif /* TEXTUREPCX_H_ */
