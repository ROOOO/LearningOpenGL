#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
in vec3 LightPos;
uniform vec3 viewPos;

float ambientStrength = 0.1f;
vec3 ambient = ambientStrength * lightColor;

vec3 lightDir = normalize(LightPos - fragPos);
vec3 norm = normalize(Normal);
float diff = max(dot(lightDir, norm), 0.0f);
vec3 diffuse = diff * lightColor;

float specularStrength = 0.5f;
vec3 viewDir = normalize(-fragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
vec3 specular = spec * specularStrength * lightColor;

vec3 result = (ambient + diffuse + specular) * objectColor;

void main() {
  color = vec4(result, 1.0f);
}