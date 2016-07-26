#version 330 core
out vec4 color;

in VS_OUT {
  vec3 normal;
  vec2 texCoords;
  vec3 fragPos;
} fs_in;

uniform sampler2D tex;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
  vec3 texColor = vec3(texture(tex, fs_in.texCoords));
  float gamma = 2.2f;
  
  vec3 ambient = vec3(0.1f) * texColor;
  
  vec3 lightDir = normalize(lightPos - fs_in.fragPos);
  vec3 normal = normalize(fs_in.normal);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = diff * vec3(pow(texColor.rgb, vec3(gamma)));
  
  vec3 viewDir = normalize(viewPos - fs_in.fragPos);
  vec3 halfwayDir = normalize(viewDir + lightDir);
  float spec = pow(max(dot(fs_in.normal, halfwayDir), 0.0f), 32.0f);
  vec3 specular = spec * texColor;

  float distance = length(viewPos - fs_in.fragPos);
  float attenuation = 1.0f / (distance * distance);
  specular = specular * attenuation;
  
  color = vec4(ambient + diffuse + specular, 1.0f);
  //color.rgb = pow(color.rgb, vec3(1.0f / gamma));
}
