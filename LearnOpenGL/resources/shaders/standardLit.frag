#version 330 core
in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

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

layout (std140) uniform PointLight
{
    float pointStrength;
    vec4 pointColor;
    vec4 lightPosition;
    float attenuation;
};

uniform sampler2D inTexture;
uniform vec4 color;

out vec4 FragColor;

void main()
{
    float directionalDot = max(dot(normal, inverseLightDirection.xyz), 0.0f);
    vec3 directional = directionalStrength * directionalDot * directionalColor.xyz;

    vec3 pointDiff = lightPosition.xyz - fragPos;
    float pointDot = max(dot(normal, normalize(pointDiff)), 0.0f);
    vec3 point = (pointStrength * pointDot * pointColor.xyz) / (1 + attenuation * length(pointDiff));

    vec3 ambient = ambientStrength * ambientColor.xyz;

    vec4 light = vec4(clamp(ambient + directional + point, 0.0f, 1.0f), 1.0f);

    FragColor = light * color * texture(inTexture, texCoord);
}