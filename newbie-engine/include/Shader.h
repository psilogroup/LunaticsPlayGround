/* File: Shader.h; Mode: C++; Tab-width: 3; Author: Simon Flannery;           */

#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
   void Load(const char*);
   void Delete();

   void Enable();
   void Disable();
   void Bind();

   void EnvParameter(unsigned int index, float, float, float, float);
   void LocalParameter(unsigned int index, float, float, float, float);

private:
   unsigned int target;
   unsigned int id;
};

#endif
