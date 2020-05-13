/*
 * XMLTagManager.cpp
 *
 *  Created on: 16/05/2009
 *      Author: newbie
 */

#include "BZK_XMLTagManager.h"
#include "BZK_ParsingTools.h"

BZK_XMLTagManager::BZK_XMLTagManager(std::string aFileName)
{
  fileName = aFileName;

}

BZK_XMLTagManager::~BZK_XMLTagManager()
{
  // TODO Auto-generated destructor stub
}

void
BZK_XMLTagManager::Add(BZK_XMLTag* tag)
{
  //tagList[tag->getTagName().c_str()] = tag;
}

World*
BZK_XMLTagManager::process()
{
  World *world = NULL;
  std::ifstream datafile;
  datafile.open(fileName.c_str());
  std::string echo;

  datafile.close();

  return world;

}
