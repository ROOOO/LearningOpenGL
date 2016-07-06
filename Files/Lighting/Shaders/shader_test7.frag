#version 330 core
out vec4 color;
in vec3 Normal;
in vec3 FragPos;
in vec2 ourTexCoord;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct DirLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
struct PointLight {
  vec3 position;
  float constant;
  float linear;
  float quadratic;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
struct SpotLight {
  float cutOff;
  float outerCutOff;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

#define NR_POINT_LIGHTS 4
uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 CalcDirectionLight(DirLight light, vec3 normal, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTexCoord));
  
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(normal, lightDir), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ourTexCoord));

  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, ourTexCoord));
  
  return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTexCoord));

  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(normal, lightDir), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ourTexCoord));

  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, ourTexCoord));

  float distance = length(light.position - fragPos);
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  return attenuation * (ambient + diffuse + specular);
}

void main() {
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 result = CalcDirectionLight(dirLight, norm, viewDir);
  for (int i = 0; i < NR_POINT_LIGHTS; i++) {
    result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
  }

  color = vec4(result, 1.0f);
}
