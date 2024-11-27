#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
out vec3 fragNormal;
out vec3 shadedcolor;
out vec4 modelpos;
out vec4 modelNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 posCam;

float coef_ambiental = 0.1;
float coef_difusa = 0.8;
float coef_spec = 0.9;
float gloss = 10.0;

vec3 matColor = vec3(1.0, 0.0, 1.0);
vec3 posLuz = vec3(-5.0);
vec3 colorLuz = vec3(0.0, 1.0, 1.0);


void main()
{

    vec4 modelpos = model * vec4(position, 1.0);
    vec3 L = normalize(posLuz - modelpos.xyz);
    modelNormal = (model * vec4(normal, 1.0));
    vec3 N = normalize(modelNormal.xyz);
    vec3 R = reflect(-L, N);
    vec3 V = normalize(posCam - modelpos.xyz);

    fragNormal = (N + 1.0) * 0.5;

    shadedcolor = coef_ambiental * matColor +
                  coef_difusa * matColor * max(dot(N, L), 0.0) +
                  colorLuz * coef_spec * pow(max(dot(V, R), 0.0), gloss);

    gl_Position = projection * view * model * vec4(position, 1.0);
}
