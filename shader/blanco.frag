#version 410 core
in vec3 fragColor;
out vec4 color;
void main()
{
    color = vec4(fragColor, 1.0);
    color = vec4(1.0);
}
