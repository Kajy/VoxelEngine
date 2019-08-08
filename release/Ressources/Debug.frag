#version 400

in vec3 Colors;
out vec4 FragColors;


void main() {
   FragColors = vec4(Colors, 1.0f);
}