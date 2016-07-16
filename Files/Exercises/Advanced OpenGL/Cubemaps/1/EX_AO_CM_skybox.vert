#version 330 core
layout (location = 0) in vec3 position;

out vec3 TexCoords;
out vec3 Normal;

uniform mat4 viewMat;
uniform mat4 projMat;

void main() {
  gl_Position = (projMat * viewMat * vec4(position, 1.0f)).xyww;
  TexCoords = position;
//  Normal = mat3(transpose(inverse(modelMat))) * position;
}
