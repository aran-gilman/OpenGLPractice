#version 330 core
in vec3 normal;
in vec2 texCoord;

// TODO: Replace vec3s with something else.
// Some std140 implementations handle vec3s incorrectly:
// https://www.khronos.org/opengl/wiki/Interface_Block_(GLSL)#Memory_layout
// float[3] is probably the easiest substitute, but they're 3x as big.
layout (std140) uniform AmbientLight
{
    float ambientStrength;
    vec3 ambientColor;
};

layout (std140) uniform DirectionalLight
{
    float directionalStrength;
    vec3 directionalColor;
    vec3 inverseLightDirection;
};

uniform sampler2D inTexture;
uniform vec4 color;

out vec4 FragColor;

void main()
{
    float directionalDot = max(dot(normal, inverseLightDirection), 0.0f);
    vec4 directional = vec4(directionalStrength * directionalDot * directionalColor, 1.0f);
    vec4 ambient = vec4(ambientStrength * ambientColor, 1.0f);
    FragColor = (ambient + directional) * color * texture(inTexture, texCoord);
}