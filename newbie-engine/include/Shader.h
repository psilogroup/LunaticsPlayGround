
#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
   void Load(std::string vertexName,std::string fragmentName);
   void Delete();

   void Enable();
   void Disable();

   void EnvParameterVec(std::string name, float x, float y, float z, float w);
   void LocalParameterVec(std::string name, float x, float y, float z, float w);

private:
   unsigned int target;
   unsigned int id;

   void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
