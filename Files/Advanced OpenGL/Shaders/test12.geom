#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
  vec2 texCoords;
} gs_in[];
out vec2 TexCoords;

uniform float time;

vec3 GetNormal() {
  vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
  vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
  return normalize(cross(a, b));
}

vec4 Explode(vec4 position, vec3 normal) {
  float magnitude = 2.0f;
  vec3 direction = normal * ((sin(time) + 1.0f) / 2.0f) * magnitude;
  return position + vec4(direction, 0.0f);
}

void main() {
  TexCoords = gs_in[0].texCoords;
  gl_Position = Explode(gl_in[0].gl_Position, GetNormal());
  EmitVertex();
  TexCoords = gs_in[1].texCoords;
  gl_Position = Explode(gl_in[1].gl_Position, GetNormal());
  EmitVertex();
  TexCoords = gs_in[2].texCoords;
  gl_Position = Explode(gl_in[2].gl_Position, GetNormal());
  EmitVertex();
  EndPrimitive();
}