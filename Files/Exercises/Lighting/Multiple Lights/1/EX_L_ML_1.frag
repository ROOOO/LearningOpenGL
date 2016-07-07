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
  float constant;
  float linear;
  float quadratic;
  vec3 direction;
  float cutOff;
  float outerCutOff;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

out vec4 color;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform DirectionLight directionLight;
#define num_of_pointLights 4
uniform PointLight pointLights[num_of_pointLights];
uniform SpotLight spotLight;

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
  
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
  
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
  
  return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
  
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

  float distance = length(light.position - fragPos);
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

  float distance = length(light.position - fragPos);
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  float epsilon = light.cutOff - light.outerCutOff;
  float theta = dot(-lightDir, normalize(light.direction));
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

  return (ambient + diffuse + specular) * attenuation * intensity;
}

void main() {
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
  
  vec3 result = CalcDirectionLight(directionLight, norm, viewDir);
  for (int i = 0; i < 4; i++) {
	result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
  }
  result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
  
  color = vec4(result, 1.0f);
}