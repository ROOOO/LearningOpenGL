#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//  Interface Blocks
out VS_OUT {
  vec2 TexCoords;
} vs_out;

void main() {
  gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0f);
  
//  gl_PointSize
//  gl_PointSize = gl_Position.z;
  
//  Interface Blocks
  vs_out.TexCoords = texCoords;
}