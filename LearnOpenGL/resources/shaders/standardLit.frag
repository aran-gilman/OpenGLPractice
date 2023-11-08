#version 330 core
in vec3 normal;
in vec2 texCoord;

layout (std140) uniform AmbientLight
{
    float ambientStrength;
    vec4 ambientColor;
};

layout (std140) uniform DirectionalLight
{
    float directionalStrength;
    vec4 directionalColor;
    vec4 inverseLightDirection;
};

uniform sampler2D inTexture;
uniform vec4 color;

out vec4 FragColor;

void main()
{
    float directionalDot = max(dot(vec4(normal, 0.0f), inverseLightDirection), 0.0f);
    vec4 directional = directionalStrength * directionalDot * directionalColor;
    vec4 ambient = ambientStrength * ambientColor;
    FragColor = (ambient + directional) * color * texture(inTexture, texCoord);
}