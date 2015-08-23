#version 330

in vec2 vUV;

out vec3 outColour;

uniform sampler2D textureSampler;

void main()
{
    outColour = texture(textureSampler, vUV).rgb;
}
