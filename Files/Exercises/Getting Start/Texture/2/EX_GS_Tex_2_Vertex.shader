#version 330 core
uniform float x;
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex;
out vec2 texCoord;
void main() {
  gl_Position = vec4(position.x + x, position.yz, 1.0f);
  texCoord = tex;
}