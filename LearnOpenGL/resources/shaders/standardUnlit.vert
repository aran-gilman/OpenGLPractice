#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (std140) uniform CameraBlock
{
    mat4 view;
    mat4 projection;
    vec4 cameraPos;
};

uniform mat4 transform;
uniform mat3 normalMatrix;

out vec3 normal;
out vec2 texCoord;
out vec3 fragPos;

void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0f);
    normal = normalMatrix * aNormal;
    texCoord = aTexCoord;
    fragPos = vec3(transform * vec4(aPos, 1.0f));
}