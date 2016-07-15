#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 Position;

uniform vec3 viewPos;
uniform samplerCube tex;

void main() {
  vec3 I = normalize(Position - viewPos);
  vec3 R = reflect(I, normalize(Normal));
//  float ratio = 1.0f / 1.52f;
//  vec3 R = refract(I, normalize(Normal), ratio);
  color = vec4(texture(tex, R));
}