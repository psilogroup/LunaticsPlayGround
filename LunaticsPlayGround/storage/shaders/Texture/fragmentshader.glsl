#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture_slot_0;

void main()
{
    FragColor = texture(texture_slot_0, TexCoord);
}