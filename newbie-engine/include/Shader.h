
#ifndef SHADER_H
#define SHADER_H
#include <string>
class Shader
{
public:
   void Load(std::string vertexName,std::string fragmentName);
   void Delete();

   void Enable();
   void Disable();

   void SetInteger(std::string name, int value);
   void SetMat4(std::string name, const float* m);

private:
   unsigned int target;
   unsigned int id;

   void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
