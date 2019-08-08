precision highp float;
attribute vec3 position;
attribute vec3 normal;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
varying vec3 fNormal;
varying vec3 fPosition;
varying vec3 intensity;
const vec4 lightLocation = vec4(0.0, 10.0, 1.0, 1.0);

const vec3 Kd = vec3(1.0, 1.0, 0.0); // diffuse object color
const vec3 Id = vec3(1.0, 1.0, 1.0); // diffuse light color

const vec3 Ka = vec3(0.2, 0.2, 0.0); // ambient object color
const vec3 Ia = vec3(1.0, 1.0, 1.0); // ambient light color

const vec3 Ks = vec3(1.0, 1.0, 1.0); // diffuse object color
const vec3 Is = vec3(1.0, 1.0, 1.0); // diffuse light color


void main()
{
  
  vec4 P = modelViewMatrix * vec4(position, 1.0); // point in a camera coord.
  vec3 L = normalize((lightLocation - P).xyz);
  
  vec3 N = normalize(normalMatrix * normal);
  vec3 V = normalize(-P.xyz);
  vec3 R = normalize(reflect(-L, N));
  vec3 diffuse = Kd * Id * max(dot(L, N), 0.0);
  vec3 ambiant = Ka * Ia;
  vec3 specular = Ks * Is * pow(dot(R, V), 50.0);
  intensity = diffuse + ambiant + specular;
  gl_Position = projectionMatrix * P;