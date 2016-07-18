#version 330 core
layout (location = 0) in vec3 position;

layout (std140) uniform Matrices {
  mat4 viewMat;
  mat4 projMat;
};
uniform mat4 modelMat;

void main() {
  gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0f);
}