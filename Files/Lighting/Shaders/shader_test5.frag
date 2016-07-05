#version 330 core
out vec4 color;
in vec3 Normal;
in vec3 FragPos;
in vec2 ourTexCoord;
uniform vec3 lightColor;
uniform vec3 viewPos;
struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};
uniform Material material;
struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float constant;
  float linear;
  float quadratic;
};
uniform Light light;

void main() {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTexCoord));
  
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(light.position - FragPos);
  float diff = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ourTexCoord));
  
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, ourTexCoord));

  float distance = length(light.position - FragPos);
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
  
  vec3 result = ambient + diffuse + specular;
  result = result * attenuation;
  
  color = vec4(result, 1.0f);
}
