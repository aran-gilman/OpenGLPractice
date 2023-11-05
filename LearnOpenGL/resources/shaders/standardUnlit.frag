#version 330 core
in vec2 texCoord;

uniform sampler2D inTexture;

uniform vec4 color;

out vec4 FragColor;

void main()
{
    FragColor = color * texture(inTexture, texCoord);
}