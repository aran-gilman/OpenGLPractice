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

struct LightProperties
{
    vec4 position;
    vec4 color;
    float attenuation;
};

layout (std140) uniform Light
{
    LightProperties directional;
    LightProperties point;
};

struct MaterialProperties
{
    sampler2D texture;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform MaterialProperties material;

out vec4 FragColor;

void main()
{
    float specularStrength = 20.0f;

    vec3 viewDir = normalize(camera.position.xyz - fragPos);

    float directionalDot = max(dot(normal, -directional.position.xyz), 0.0f);
    vec3 directional = directional.color.w * directionalDot * directional.color.xyz;

    vec3 pointDiff = point.position.xyz - fragPos;
    vec3 pointDir = normalize(pointDiff);
    float pointDot = max(dot(normal, pointDir), 0.0f);
    vec3 point = (point.color.w * pointDot * point.color.xyz) / (1 + point.attenuation * length(pointDiff));

    //vec3 reflectDirectional = reflect(directional.position.xyz, normal);
    //float specMultDirectional = pow(max(dot(viewDir, reflectDirectional), 0.0f), 32) * specularStrength;
    //vec3 directionalSpecular = specMultDirectional * directional.color.xyz;

    //vec3 reflectPoint = reflect(-pointDir, normal);
    //float specMultPoint = pow(max(dot(viewDir, reflectPoint), 0.0f), 32) * specularStrength;
    //vec3 pointSpecular = (specMultPoint * point.color.xyz)  / (1 + point.attenuation * length(pointDiff));

    //vec3 specularLight = directionalSpecular + pointSpecular;

    vec3 ambient = material.ambient * world.ambientLight.xyz;
    vec3 diffuse = material.diffuse * directional + point;
    vec3 specular = vec3(0.0f); //material.specular * directionalSpecular + pointSpecular;

    FragColor = vec4(ambient + diffuse + specular, 1.0f) * texture(material.texture, texCoord);
}