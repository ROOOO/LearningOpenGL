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

out vec4 color;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform DirectionLight directionLight;
#define num_of_pointLights 4
uniform PointLight pointLights[num_of_pointLights];

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
  
  vec3 lightDir = normalize(light.direction);
  float diff = max(dot(-lightDir, normal), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
  
  float spec = pow(max(dot(viewDir, normal), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
  
  return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
  
  vec3 lightDir = normalize(light.position - fragPos);
}

void main() {
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
  
  vec3 result = CalcDirectionLight(directionLight, norm, viewDir);
  
  color = vec4(result, 1.0f);
}