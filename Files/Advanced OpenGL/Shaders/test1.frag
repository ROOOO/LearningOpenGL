#version 330 core
out vec4 color;

in vec2 TexCoords;

uniform sampler2D tex;

float LinearizeDepth(float depth) {
  float near = 0.1f;
  float far = 100.0f;
  float z = depth * 2.0f - 1.0f;
  return (2.0f * near) / (far + near - z * (far - near));
}

void main() {
  color = vec4(texture(tex, TexCoords));
//  color = vec4(vec3(gl_FragCoord.z), 1.0f);
//  color = vec4(vec3(LinearizeDepth(gl_FragCoord.z)), 1.0f);
}