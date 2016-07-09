#version 330 core

struct Material {
  sampler2D texture_diffuse1;
  sampler2D texture_specular1;
  float shininess;
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

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
#define NR_Point_Lights 2
uniform PointLight pointLights[NR_Point_Lights];

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
  vec3 result;
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
  
  for (int i = 0; i < NR_Point_Lights; i++) {
    result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
  }
  
  color = vec4(result, 1.0f);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
  
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
  
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords));
  
  float dis = length(light.position - fragPos);
  float attenuation = 1.0f / (light.constant + light.linear * dis + light.quadratic * (dis * dis));
  
  return (ambient + diffuse + specular) * attenuation;
}
