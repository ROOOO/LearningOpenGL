#version 330 core

out vec4 fragColor;

in VS_OUT {
  vec3 normal;
  vec3 fragPos;
  vec2 texCoords;
} fs_in;

uniform sampler2D tex;
uniform vec3 lightPos[4];
uniform vec3 lightColor[4];
uniform vec3 viewPos;
uniform bool gamma;

vec3 BlinnPhong(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 lightColor) {
  vec3 lightDir = normalize(lightPos - fragPos);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = diff * lightColor;
  
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 halfwayDir = normalize(viewDir + lightDir);
  float spec = pow(max(dot(normal, halfwayDir), 0.0f), 64.0f);
  vec3 specular = spec * lightColor;
  
  float dis = length(lightPos - fragPos);
//  float attenuation = 1.0f / dis;
  float attenuation = 1.0f / (dis * dis);
  
  return (diffuse + specular) * attenuation;
}

void main() {
  vec3 color = texture(tex, fs_in.texCoords).rgb;
  vec3 lighting = vec3(0.0f);
  for (int i = 0; i < 4; i++) {
    lighting += BlinnPhong(fs_in.normal, fs_in.fragPos, lightPos[i], lightColor[i]);
  }
  color *= lighting;
  if (gamma) {
    color = pow(color, vec3(1.0f / 2.2f));
  }
  
  fragColor = vec4(color, 1.0f);
}
