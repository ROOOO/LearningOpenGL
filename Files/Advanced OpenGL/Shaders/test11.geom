#version 330 core
layout (points) in;
//layout (points, max_vertices = 1) out;
layout (triangle_strip, max_vertices = 5) out;

in VS_OUT {
  vec3 color;
} gs_in[];

out vec3 fColor;

void buildHouses(vec4 position) {
  fColor = gs_in[0].color;
  gl_Position = position + vec4(-0.2f, -0.2f, -0.0f, 0.0f);
  EmitVertex();
  gl_Position = position + vec4(0.2f, -0.2f, -0.0f, 0.0f);
  EmitVertex();
  gl_Position = position + vec4(-0.2f, 0.2f, -0.0f, 0.0f);
  EmitVertex();
  gl_Position = position + vec4(0.2f, 0.2f, -0.0f, 0.0f);
  EmitVertex();
  gl_Position = position + vec4(0.0f, 0.4f, 0.0f, 0.0f);
  fColor = vec3(1.0f);
  EmitVertex();
  EndPrimitive();
}

void main() {
//  4 points
//  gl_Position = gl_in[0].gl_Position;
//  EmitVertex();
//  EndPrimitive();
  
//  4 houses
  buildHouses(gl_in[0].gl_Position);
}