#version 330 core
out vec4 color;

in VS_OUT {
  vec2 texCoords;
} fs_in;

uniform sampler2D tex;
uniform float farPlane;
uniform float nearPlane;

float LinearizeDepth(float depth) {
  float z = depth * 2.0f - 1.0f;
  return (2 * farPlane * nearPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}

void main() {
  float depthValue = texture(tex, fs_in.texCoords).r;
//  color = vec4(vec3(depthValue), 1.0f);
  color = vec4(vec3(LinearizeDepth(depthValue) / farPlane), 1.0f);
}
