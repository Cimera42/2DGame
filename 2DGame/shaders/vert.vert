#version 330

in vec2 vertPos;
in vec4 vertUV;

in mat4 instanceMatrix;

out vec2 vUV;

uniform mat4 viewProjMat;

void main()
{
    vec2 corner = vertPos+vec2(0.5,0.5);
    vec2 offset = corner*vertUV.zw;
    vUV = (vertUV.xy + offset)*vec2(1,-1);
    gl_Position = viewProjMat * instanceMatrix * vec4(vertPos,0,1);
}
