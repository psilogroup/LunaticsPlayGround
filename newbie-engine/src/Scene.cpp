/*
 * Scene.cpp
 *
 *  Created on: 21/07/2009
 *      Author: newbie
 */

#include "Scene.h"

Scene::Scene()
{
  camera = new Camera();

}

Scene::~Scene()
{
  delete camera;
}
