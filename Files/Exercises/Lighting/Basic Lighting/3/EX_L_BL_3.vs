#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 fragPos;
out vec3 LightPos;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform vec3 lightPos;

void main() {
  gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0f);
  Normal = mat3(transpose(inverse(viewMat * modelMat))) * normal;
  fragPos = vec3(viewMat * modelMat * vec4(position, 1.0f));
  LightPos = vec3(viewMat * vec4(lightPos, 1.0f));
}
