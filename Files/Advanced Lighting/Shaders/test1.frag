#version 330 core
out vec4 color;

in VS_OUT {
  vec2 texCoords;
  vec3 normal;
  vec3 fragPos;
} fs_in;

uniform sampler2D tex;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool blinn;

void main() {
  vec3 texColor = (texture(tex, fs_in.texCoords)).rgb;
  
  vec3 ambient = 0.05 * texColor;
  
  vec3 lightDir = normalize(lightPos - fs_in.fragPos);
  vec3 normal = normalize(fs_in.normal);
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 diffuse = diff * texColor;
  
  vec3 viewDir = normalize(viewPos - fs_in.fragPos);
  float spec = 0.0f;
  
  if (blinn) {
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0f), 32.0f);
  } else {
    vec3 reflectDir = reflect(-lightDir, normal);
    spec = pow(max(dot(viewDir, reflectDir), 0.0f), 8.0f);
  }
  vec3 specular = vec3(0.3f) * spec;
//
//  color = vec4(texture(tex, fs_in.texCoords));
  color = vec4(ambient + diffuse + specular, 1.0f);
}