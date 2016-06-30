#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 ourColor;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
  gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0f);

float ambientStrength = 0.1f;
vec3 ambient = ambientStrength * lightColor;

vec3 norm = normalize(mat3(transpose(inverse(modelMat))) * normal);
vec3 fragPos = vec3(modelMat * vec4(position, 1.0f));
vec3 lightDir = normalize(lightPos - fragPos);
float diff = max(dot(lightDir, norm), 0.0f);
vec3 diffuse = diff * lightColor;

float specularStrength = 1.0f;
vec3 reflectDir = reflect(-lightDir, norm);
vec3 viewDir = normalize(viewPos - fragPos);
float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
vec3 specular = spec * specularStrength * lightColor;

vec3 result = (ambient + diffuse + specular);

  ourColor = result;
}