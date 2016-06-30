#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 fragPos;

uniform vec3 viewPos;

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};
uniform Material material;

struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
uniform Light light;

void main() {
  vec3 ambient = light.ambient * material.ambient;
  
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, norm), 0.0f);
  vec3 diffuse = light.diffuse * (diff * material.diffuse);
  
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3 specular = light.specular * (spec * material.specular);
  
  vec3 result = ambient + diffuse + specular;
  color = vec4(result, 1.0f);
}