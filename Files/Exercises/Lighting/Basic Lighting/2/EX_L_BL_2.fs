#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

float ambientStrength = 0.1f;
vec3 ambient = ambientStrength * objectColor;

vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightPos - fragPos);
float diff = max(dot(lightDir, norm), 0.0f);
vec3 diffuse = diff * objectColor;

float specularStrength = 0.5f;
vec3 reflectDir = reflect(-lightDir, norm);
vec3 viewDir = normalize(viewPos - fragPos);
float spec = pow(max(dot(reflectDir, viewDir), 0.0f), 32);
vec3 specular = spec * specularStrength * objectColor;

vec3 result = (ambient + diffuse + specular) * lightColor;

void main() {
  color = vec4(result, 1.0f);
}