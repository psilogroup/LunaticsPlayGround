/*
 * Scene.h
 *
 *  Created on: 21/07/2009
 *      Author: newbie
 */

#ifndef __SCENE__
#define __SCENE__
#include "Camera.h"
#include "baselib.h"

class Scene
{
public:
  Camera *camera;
  Scene();
  virtual
  ~Scene();
};

#endif /* SCENE_H_ */
