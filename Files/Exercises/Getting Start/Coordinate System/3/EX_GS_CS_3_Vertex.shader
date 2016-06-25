#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
out vec2 ourTexCoord;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
void main() {
  gl_Position = projMat * viewMat * modelMat * vec4(position.x, -position.y, position.z, 1.0f);
  ourTexCoord = texCoord;
}