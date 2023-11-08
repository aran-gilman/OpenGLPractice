#version 330 core
in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

layout (std140) uniform CameraBlock
{
    mat4 view;
    mat4 projection;
    vec4 cameraPos;
};

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
    float specularStrength = 20.0f;

    vec3 viewDir = normalize(cameraPos.xyz - fragPos);

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

    vec3 specular = directionalSpecular + pointSpecular;

    vec3 ambient = ambientStrength * ambientColor.xyz;

    vec4 light = vec4(ambient + directional + point + specular, 1.0f);
    //vec4 light = vec4(specular, 1.0f);

    FragColor = light * color * texture(inTexture, texCoord);
}