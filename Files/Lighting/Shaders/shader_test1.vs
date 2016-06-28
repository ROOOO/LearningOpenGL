#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
out vec3 Normal;

void main() {
  gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0f);
  Normal = normal;
}