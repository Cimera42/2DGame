#version 330

in vec2 vertPos;
in vec2 vertUV;

out vec2 vUV;

uniform mat4 modelMat;

void main()
{
    vUV = vertUV*vec2(1,-1);
    gl_Position = modelMat * vec4(vertPos,0,1);
}
