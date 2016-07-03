#version 330 core
out vec4 color;

in vec2 ourTexCoord;
in vec3 Normal;
in vec3 fragPos;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};
uniform Material material;

struct Light {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 position;
};
uniform Light light;

uniform vec3 camPos;

void main() {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTexCoord));
  
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, norm), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ourTexCoord));
  
  vec3 viewDir = normalize(camPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, ourTexCoord));
  
  color = vec4(ambient + diffuse + specular, 1.0f);
}