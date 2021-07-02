#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;

out vec3 vertexcolor;
out vec2 outUV;
uniform float PI;
uniform float time;
uniform mat4 transformMatrix;
float angle = 25.0f * PI/180.0f;
// Order is important : Scale -> Rotate -> Translate
void main()
{
   //scaleMatrix[0][0] = scaleMatrix[1][1] = (sin(time*0.1) / 2.0f) + 0.5f;
   vec4 newPos = transformMatrix * vec4(position, 1.0);
   //newPos = vec4(position, 1.f);
   gl_Position = newPos;
   vertexcolor = color;
   outUV = uv;
}