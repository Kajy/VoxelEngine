#version 400

in vec4 Position;
in vec3 Normal;
in vec3 Colors;
in vec2 Textures;

struct LightInfo {
vec4 Position; // Light position in eye coords.
vec3 Color;
vec3 Intensity;
float Power;
};

uniform LightInfo Lights[32];
uniform int nbLights;


struct MaterialInfo {
vec3 Ka; // Ambient reflectivity
vec3 Kd; // Diffuse reflectivity
vec3 Ks; // Specular reflectivity
float Shiness; // Specular shininess factor (phong exponent)
};

uniform MaterialInfo Material;

uniform sampler2D Text1;
uniform bool isText;

out vec4 FragColors;


void main() {
   vec3 LightIntensity = vec3(0,0,0);
   vec3 Ambiant = vec3(0.4, 0.4, 0.4);

   for (int i = 0; i < nbLights; i++)
   {
		float D = distance(Lights[i].Position.xyz, Position.xyz);
		vec3 L = normalize((Lights[i].Position - Position).xyz);
		vec3 V = normalize(-Position.xyz);
		vec3 R = normalize(reflect(-L, Normal));
		vec3 diffuse = Material.Kd * (Lights[i].Color * Lights[i].Intensity) * max(dot(L, Normal), 0.0);
		vec3 specular = Material.Ks * (Lights[i].Color * Lights[i].Intensity) * pow(max(dot(R, V), 0.0), Material.Shiness);
		LightIntensity = LightIntensity + ((diffuse + specular));// / pow(D, Lights[i].Power));
	}
	//LightIntensity = vec3(1,1,1);
	if (isText) {
		vec4 texColor = texture(Text1, Textures);
		FragColors = vec4(LightIntensity + Ambiant, 1.0) * texColor;
   }
   else {
		FragColors = vec4(LightIntensity, 1.0) * vec4(Colors, 1.0);
   }
}