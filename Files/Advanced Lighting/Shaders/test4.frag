#version 330 core
out vec4 fragColor;

in VS_OUT {
  vec2 texCoords;
  vec3 normal;
  vec3 fragPos;
  vec4 fragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;
uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace) {
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  projCoords = projCoords * 0.5f + 0.5f;
  float closestDepth = texture(shadowMap, projCoords.xy).r;
  float currentDepth = projCoords.z;
  float shadow = currentDepth > closestDepth ? 1.0f : 0.0f;
  return shadow;
}

void main() {
  vec3 color = texture(diffuseTexture, fs_in.texCoords).rgb;
  vec3 normal = normalize(fs_in.normal);
  vec3 lightColor = vec3(1.0f);
  
  vec3 ambient = 0.15f * lightColor;
  
  vec3 lightDir = normalize(lightPos - fs_in.fragPos);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = diff * lightColor;
  
  vec3 viewDir = normalize(viewPos - fs_in.fragPos);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(viewDir, halfwayDir), 0.0f), 64.0f);
  vec3 specular = spec * lightColor;
  
  float shadow = ShadowCalculation(fs_in.fragPosLightSpace);
  vec3 lighting = (ambient + (1 - shadow) * (diffuse + specular)) * color;
  
//  fragColor = vec4(1.0f);
  fragColor = vec4(lighting, 1.0f);
}