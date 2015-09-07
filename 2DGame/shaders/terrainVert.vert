#version 330

in vec2 vertPos;
in vec2 vertUV;

out vec2 vUV;

uniform mat4 modelMat;
uniform mat4 viewProjMat;

void main()
{
    vUV = vertUV*vec2(1,-1);
    gl_Position = viewProjMat * modelMat * vec4(vertPos,0,1);
}
