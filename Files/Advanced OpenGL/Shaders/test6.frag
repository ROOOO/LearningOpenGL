#version 330 core
out vec4 color;
in vec2 TexCoords;
uniform sampler2D tex;
void main() {
//  color = vec4(texture(tex, TexCoords));
  
//  Inversion
//  color = vec4(vec3(1.0f - texture(tex, TexCoords)), 1.0f);
  
//  Grayscale
//  color = texture(tex, TexCoords);
//  float average = (color.r + color.g + color.b) / 3.0f;
//  float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
//  color = vec4(average, average, average, 1.0f);
  
//  Kernel effects
  const float offset = 1.0f / 300;
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
//  float kernel[9] = float[] (
//    -1, -1, -1,
//    -1, 9, -1,
//    -1, -1, -1
//  );
  float kernel[9] = float[] (
                             1.0f / 16, 2.0f / 16, 1.0f / 16,
                             2.0f / 16, 4.0f / 16, 2.0f / 16,
                             1.0f / 16, 2.0f / 16, 1.0f / 16
                             );
//  float kernel[9] = float[] (
//                             1.0f, 1.0f, 1.0f,
  //                           1.0f, -8.0f, 1.0f,
    //                         1.0f, 1.0f, 1.0f
      //                       );
  vec3 sampleTex[9];
  for (int i = 0; i < 9; i++) {
    sampleTex[i] = vec3(texture(tex, TexCoords.st + offsets[i]));
  }
  vec3 col;
  for (int i = 0; i < 9; i++) {
    col += sampleTex[i] * kernel[i];
  }
  color = vec4(col, 1.0f);
}