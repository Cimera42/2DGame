#version 330

in vec2 vertPos;
in vec2 vertUV;

in mat4 instanceMatrix;

out vec2 vUV;

void main()
{
    vUV = vertUV*vec2(1,-1);
    gl_Position = instanceMatrix * vec4(vertPos,0,1);
}
