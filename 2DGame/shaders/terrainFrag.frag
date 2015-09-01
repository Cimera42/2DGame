#version 330

in vec2 vUV;

out vec4 outColour;

uniform sampler2D textureSampler;

void main()
{
    outColour = texture(textureSampler, vUV);
}
