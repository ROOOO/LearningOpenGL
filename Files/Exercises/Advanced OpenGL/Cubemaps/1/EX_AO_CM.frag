#version 330 core
out vec4 color;

in vec3 Normal;
in vec2 TexCoords;
in vec3 Position;

uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_reflection1;
uniform samplerCube tex;

void main() {
  vec4 diffuse = texture(texture_diffuse1, TexCoords);
  vec3 I = normalize(Position - viewPos);
  vec3 R = reflect(I, normalize(Normal));
  float reflect_intensity = texture(texture_reflection1, TexCoords).r;
  vec4 reflection;
  if (reflect_intensity > 0.1) {
    reflection = texture(tex, R) * reflect_intensity;
  }
//  color = vec4(texture(tex, R));
  color = diffuse + reflection;
}