#version 410 core

in vec4 modelpos;
in vec4 modelNormal;

uniform vec3 posCam;

float coef_ambiental = 0.1;
float coef_difusa = 0.8;
float coef_spec = 0.9;
float gloss = 50.0;

vec3 matColor = vec3(1.0, 0.0, 1.0);
vec3 posLuz = vec3(-5.0);
vec3 colorLuz = vec3(0.0, 1.0, 1.0);

out vec4 color;

void main()
{
    vec3 L = normalize(posLuz - modelpos.xyz);
    vec3 N = normalize(modelNormal.xyz);
    vec3 R = reflect(-L, N);
    vec3 V = normalize(posCam - modelpos.xyz);
    vec3 H = normalize(L + V);

    vec3 shadedcolor = coef_ambiental * matColor +
                  coef_difusa * matColor * max(dot(N, L), 0.0) +
                  // colorLuz * coef_spec * pow(max(dot(V, R), 0.0), gloss);
                  colorLuz * coef_spec * pow(max(dot(N, H), 0.0), gloss);

    color = vec4(shadedcolor, 1.0);
}
