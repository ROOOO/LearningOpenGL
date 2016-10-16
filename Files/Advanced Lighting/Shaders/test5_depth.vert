#version 330 core
layout (location = 0) in vec3 postion;
uniform mat4 modelMat;
void main() {
  gl_Position = modelMat * vec4(postion, 1.0f);
}