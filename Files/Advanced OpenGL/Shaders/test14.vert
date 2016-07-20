#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 offset;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//uniform vec2 offsets[100];

out vec3 fColor;

void main() {
//  gl_Position = vec4(position + offsets[gl_InstanceID], 0.0f, 1.0f);
//  gl_Position = vec4(position + offset, 0.0f, 1.0f);
  vec2 pos = position * (gl_InstanceID / 100.0f);
  gl_Position = vec4(pos + offset, 0.0f, 1.0f);
  fColor = color;
}