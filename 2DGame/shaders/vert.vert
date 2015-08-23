#version 330

in vec3 vertPos;
in vec2 vertUV;

out vec2 vUV;

void main()
{
    vUV = vertUV*vec2(1,-1);
    gl_Position = vec4(vertPos,1);
}
