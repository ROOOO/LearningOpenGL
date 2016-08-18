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
uniform bool pcf;

vec2 texelSize = 1.0f / textureSize(shadowMap, 0);

float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir, vec3 normal) {
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  projCoords = projCoords * 0.5f + 0.5f;
  float currentDepth = projCoords.z;
  float bias = max(0.05f * (1.0f - dot(lightDir, normal)), 0.005f);

  float shadow = 0.0f;
  if (!pcf) {
    float closestDepth = texture(shadowMap, projCoords.xy).r;
	shadow = currentDepth - bias > closestDepth ? 1.0f : 0.0f;
  } else {
	// PCF
	for (int x = -1; x < 1; x++) {
	  for (int y = -1; y < 1; y++) {
		float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
		shadow += currentDepth - bias > pcfDepth ? 1.0f : 0.0f;
	  }
	}
    shadow /= 4.0f;
  }

  if (projCoords.z > 1.0f) {
    shadow = 0.0f;
  }
  return shadow;
}

void main() {
  vec3 color = texture(diffuseTexture, fs_in.texCoords).rgb;
  vec3 normal = normalize(fs_in.normal);
  vec3 lightColor = vec3(0.8f);
  
  vec3 ambient = 0.15f * lightColor;
  
  vec3 lightDir = normalize(lightPos - fs_in.fragPos);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = diff * lightColor;
  
  vec3 viewDir = normalize(viewPos - fs_in.fragPos);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(normal, halfwayDir), 0.0f), 64.0f);
  vec3 specular = spec * lightColor;
  
  float shadow = ShadowCalculation(fs_in.fragPosLightSpace, lightDir, normal);
  vec3 lighting = (ambient + (1 - shadow) * (diffuse + specular)) * color;
  
  fragColor = vec4(lighting, 1.0f);
//  fragColor = vec4(shadow, 0.0f, 0.0f, 1.0f);
}