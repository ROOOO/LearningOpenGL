#version 330 core
out vec4 color;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
in vec3 Normal;

float ambientStrength = 0.1f;
vec3 ambient = ambientStrength * lightColor;
vec3 result = ambient * objectColor;

void main() {
  color = vec4(result, 1.0f);
}