#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
out vec2 TexCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main() {
  gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0);
  TexCoord = vec2(texCoord.x, 1 - texCoord.y);
}
