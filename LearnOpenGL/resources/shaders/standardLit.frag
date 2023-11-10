#version 330 core
in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

layout (std140) uniform Camera
{
    mat4 view;
    mat4 projection;
    vec4 position;
} camera;

layout (std140) uniform World
{
    vec4 ambientLight;
} world;

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

struct Material
{
    sampler2D texture;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;

out vec4 FragColor;

void main()
{
    float specularStrength = 20.0f;

    vec3 viewDir = normalize(camera.position.xyz - fragPos);

    float directionalDot = max(dot(normal, inverseLightDirection.xyz), 0.0f);
    vec3 directional = directionalStrength * directionalDot * directionalColor.xyz;

    vec3 pointDiff = lightPosition.xyz - fragPos;
    vec3 pointDir = normalize(pointDiff);
    float pointDot = max(dot(normal, pointDir), 0.0f);
    vec3 point = (pointStrength * pointDot * pointColor.xyz) / (1 + attenuation * length(pointDiff));

    vec3 reflectDirectional = reflect(-inverseLightDirection.xyz, normal);
    float specMultDirectional = pow(max(dot(viewDir, reflectDirectional), 0.0f), 32) * specularStrength;
    vec3 directionalSpecular = specMultDirectional * directionalColor.xyz;

    vec3 reflectPoint = reflect(-pointDir, normal);
    float specMultPoint = pow(max(dot(viewDir, reflectPoint), 0.0f), 32) * specularStrength;
    vec3 pointSpecular = (specMultPoint * pointColor.xyz)  / (1 + attenuation * length(pointDiff));

    vec3 specularLight = directionalSpecular + pointSpecular;

    vec3 ambient = material.ambient * world.ambientLight.xyz;
    vec3 diffuse = material.diffuse * directional + point;
    vec3 specular = material.specular * directionalSpecular + pointSpecular;

    FragColor = vec4(ambient + diffuse + specular, 1.0f) * texture(material.texture, texCoord);
}