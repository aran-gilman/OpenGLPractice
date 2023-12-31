#version 330 core
#define MAX_LIGHTS 4

in VS_OUT
{
    vec3 normal;
    vec2 texCoord;
    vec3 fragPos;
} fs_in;

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

    vec4 diffuse;
    vec4 specular;

    float attenuation;
};

layout (std140) uniform Light
{
    LightProperties[MAX_LIGHTS] lights;
};

struct MaterialProperties
{
    sampler2D diffuseTexture;
    sampler2D specularTexture;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};

uniform MaterialProperties material;

out vec4 FragColor;

float CalculateAttenuation(in LightProperties light)
{
    return 1.0f + light.attenuation * length(light.position.xyz - fs_in.fragPos);
}

vec3 CalculateDiffuse(in LightProperties light)
{
    vec3 direction = light.position.w > 0.0f ? normalize(light.position.xyz - fs_in.fragPos) : -light.position.xyz;
    float dot = max(dot(fs_in.normal, direction), 0.0f);
    vec3 color = dot * light.diffuse.w * light.diffuse.xyz;
    float attenuation = CalculateAttenuation(light);
    return color / attenuation;
}

vec3 CalculateSpecular(in LightProperties light, in vec3 viewDir)
{
    vec3 direction = light.position.w > 0.0f ? -normalize(light.position.xyz - fs_in.fragPos) : light.position.xyz;
    vec3 reflectDir = reflect(direction, fs_in.normal);
    float multiplier = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 color = multiplier * light.specular.w * light.specular.xyz;
    float attenuation = CalculateAttenuation(light);
    return color / attenuation;;
}

void main()
{
    // Calculate lighting independent of material
    vec3 viewDir = normalize(camera.position.xyz - fs_in.fragPos);   
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        diffuse += CalculateDiffuse(lights[i]);
        specular += CalculateSpecular(lights[i], viewDir);
    }

    // Adjust colors based on material
    vec3 ambient = material.ambient * world.ambientLight.xyz;
    diffuse *= material.diffuse;
    specular *= material.specular;

    vec4 diffuseTexture = texture(material.diffuseTexture, fs_in.texCoord);
    vec3 result = (ambient + diffuse) * diffuseTexture.xyz;
    result += specular * texture(material.specularTexture, fs_in.texCoord).xyz;

    FragColor = vec4(result, diffuseTexture.a);
}