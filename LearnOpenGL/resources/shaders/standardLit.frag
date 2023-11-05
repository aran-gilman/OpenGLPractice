#version 330 core
in vec2 texCoord;

layout (std140) uniform AmbientLight
{
    float ambientStrength;
    vec3 ambientColor;
};

uniform sampler2D inTexture;
uniform vec4 color;

out vec4 FragColor;

void main()
{
    vec4 ambient = vec4(ambientStrength * ambientColor, 1.0f);
    FragColor = ambient * color * texture(inTexture, texCoord);
}