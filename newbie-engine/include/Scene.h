/*
 * Scene.h
 *
 *  Created on: 21/07/2009
 *      Author: newbie
 */

#ifndef __SCENE__
#define __SCENE__
#ifdef WIN32
#include <windows.h>
#endif
#include "Camera.h"

class Scene
{
public:
  Camera *camera;
  Scene();
  virtual
  ~Scene();
};

#endif /* SCENE_H_ */
