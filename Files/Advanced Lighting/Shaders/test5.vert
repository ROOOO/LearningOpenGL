#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out VS_OUT {
  vec3 fragPos;
  vec3 normal;
  vec2 texCoords;
} vs_out;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main() {
  gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0f);
  vs_out.fragPos = vec3(modelMat * vec4(position, 1.0f));
  vs_out.normal = transpose(inverse(mat3(modelMat))) * normal;
  vs_out.texCoords = texCoords;
}
