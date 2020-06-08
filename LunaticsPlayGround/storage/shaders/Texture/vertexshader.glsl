#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 TexCoord;

void main()
{
    gl_Position = u_projection * u_view * u_model * gl_Vertex;

    TexCoord = a_TexCoord;
}