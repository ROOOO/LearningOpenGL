#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
out vec3 Normal;
out vec3 FragPos;
out vec2 ourTexCoord;

void main() {
  gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0f);
  Normal = mat3(transpose(inverse(modelMat))) * normal;
  FragPos = vec3(modelMat * vec4(position, 1.0f));
  ourTexCoord = texCoord;
}
