#version 330 core
out vec4 color;
in vec2 TexCoords;

uniform sampler2D tex;

void main() {
  const float offset = 1.0f / 800;
  vec2 offsets[9] = vec2[] (
                            vec2(-offset, offset),
                            vec2(0.0f, offset),
                            vec2(offset, offset),
                            vec2(-offset, 0.0f),
                            vec2(0.0f, 0.0f),
                            vec2(offset, 0.0f),
                            vec2(-offset, -offset),
                            vec2(0.0f, -offset),
                            vec2(offset, -offset)
                            );
  float kernel[9] = float[] (
                             1.0f / 16, 2.0f / 16, 1.0f / 16,
                             2.0f / 16, 4.0f / 16, 2.0f / 16,
                             1.0f / 16, 2.0f / 16, 1.0f / 16
                             );
  vec3 sampleTex[9];
  for (int i = 0; i < 9; i++) {
    sampleTex[i] = vec3(texture(tex, TexCoords.st + offsets[i]));
  }
  vec3 col;
  for (int i = 0; i < 9; i++) {
    col += sampleTex[i] * kernel[i];
  }
//  color = vec4(col, 1.0f);
  color = vec4(texture(tex, TexCoords));
}
