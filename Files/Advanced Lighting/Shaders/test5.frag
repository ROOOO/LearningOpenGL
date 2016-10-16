#version 330 core
out vec4 fragColor;

in VS_OUT {
  vec3 fragPos;
  vec3 normal;
  vec2 texCoords;
} fs_in;

uniform sampler2D diffuseTexture;
uniform samplerCube depthMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float farPlane;

float ShadowCalculation(vec3 fragPos) {
  vec3 fragToLight = fragPos - lightPos;
  float closestDepth = texture(depthMap, fragToLight).r;
  closestDepth *= farPlane;

  float currentDepth = length(fragToLight);
  float bias = 0.05f;
//  return closestDepth;
  return currentDepth - bias > closestDepth ? 1.0f : 0.0f;
}

void main() {
  vec3 color = texture(diffuseTexture, fs_in.texCoords).rgb;
  vec3 normal = normalize(fs_in.normal);
  vec3 lightColor = vec3(0.3f);
  
  vec3 ambient = 0.3 * color;
  
  vec3 lightDir = normalize(lightPos - fs_in.fragPos);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = diff * lightColor;
  
  vec3 viewDir = normalize(viewPos - fs_in.fragPos);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(halfwayDir, normal), 0.0f), 64);
  vec3 specular = spec * lightColor;
  
  float shadow = ShadowCalculation(fs_in.fragPos);
  vec3 lighting = ambient + ((1 - shadow) * (diffuse + specular)) * color;
  
  fragColor = vec4(lighting, 1.0f);
}
