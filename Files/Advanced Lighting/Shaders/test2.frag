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
  
  vec3 ambient = vec3(0.1f) * texColor;
  
  vec3 lightDir = normalize(lightPos - fs_in.fragPos);
  vec3 normal = normalize(fs_in.normal);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = diff * texColor;
  
  vec3 viewDir = normalize(viewPos - fs_in.fragPos);
  vec3 halfwayDir = normalize(viewDir + lightDir);
  float spec = pow(max(dot(fs_in.normal, halfwayDir), 0.0f), 32.0f);
  vec3 specular = spec * texColor;
  
  color = vec4(ambient + diffuse + specular, 1.0f);
}
