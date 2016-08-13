#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out VS_OUT {
  vec2 texCoords;
} vs_out;

//uniform mat4 modelMat;
//uniform mat4 viewMat;
//uniform mat4 projMat;

void main() {
//  gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0f);
  gl_Position = vec4(position, 1.0f);
  vs_out.texCoords = texCoords;
}