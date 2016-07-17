#version 330 core
out vec4 color;

// Interface Blocks
in VS_OUT {
  vec2 TexCoords;
} fs_in;

void main() {
// FragCoord
//  if (gl_FragCoord.x < 800) {
//    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//  } else {
//    color = vec4(1.0f);
//  }
  
// FrontFacing
//  if (gl_FrontFacing) {
//    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//  } else {
//    color = vec4(1.0f);
//  }
  
// FragDepth
//  gl_FragDepth = 0.0;
  
//  Interface Blocks
  color = vec4(fs_in.TexCoords, 0.0f, 1.0f);
}