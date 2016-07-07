#version 330 core

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};
struct DirectionLight {
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
  vec3 position;
  vec3 direction;
  float cutOff;
  float outerCutOff;
  float constant;
  float linear;
  float quadratic;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform DirectionLight directionLight;
#define NR_PointLight 4
uniform PointLight pointLights[NR_PointLight];
uniform SpotLight spotLight;

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
  vec3 result;
  vec3 norm = Normal;
  vec3 viewDir = normalize(viewPos - FragPos);
  
  result = CalcDirectionLight(directionLight, norm, viewDir);
  
  for (int i = 0; i < 4; i++) {
    result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
  }
  
  result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
  
  color = vec4(result, 1.0f);
}

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
  
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(reflectDir, normal), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
  
  return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
  
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
  
  float dis = length(light.position - fragPos);
  float attenuation = 1.0f / (light.constant + light.linear * dis + light.quadratic * (dis * dis));
  
  return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
  
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
  
  float dis = length(light.position - fragPos);
  float attenuation = 1.0f / (light.constant + light.linear * dis + light.quadratic * (dis * dis));
  
  float epsilon = light.cutOff - light.outerCutOff;
  float theta = dot(-light.direction, lightDir);
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
  
  return (ambient + diffuse + specular) * attenuation * intensity;
}
