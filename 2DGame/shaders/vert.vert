#version 330

in vec2 vertPos;
in vec4 vertUV;

in mat4 instanceMatrix;

out vec2 vUV;

void main()
{
    vec2 corner = vertPos+vec2(0.5,0.5);
    vUV = vertUV.xy + corner*vertUV.zw*vec2(1,-1);
    gl_Position = instanceMatrix * vec4(vertPos,0,1);
}
