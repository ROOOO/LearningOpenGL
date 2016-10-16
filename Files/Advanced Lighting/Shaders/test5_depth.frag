#version 330 core
in vec4 fragPos;

uniform vec3 lightPos;
uniform float farPlane;

void main() {
  float lightDistance = length(fragPos.xyz - lightPos);
  lightDistance /= farPlane;
  gl_FragDepth = gl_FragCoord.z;
}
