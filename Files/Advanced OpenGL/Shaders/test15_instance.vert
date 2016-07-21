#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in mat4 instanceMatrix;

uniform mat4 viewMat;
uniform mat4 projMat;

out vec2 TexCoords;

void main() {
  gl_Position = projMat * viewMat * instanceMatrix * vec4(position, 1.0f);
  TexCoords = texCoords;
}