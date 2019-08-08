#version 400

in vec3 DebugPosition;
in vec3 DebugColors;


uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

out vec3 Colors;

void main(void)
{
   Colors = DebugColors;
   vec4 Position = ModelViewMatrix * vec4(DebugPosition, 1.0f);
   gl_Position = ProjectionMatrix * Position;
}