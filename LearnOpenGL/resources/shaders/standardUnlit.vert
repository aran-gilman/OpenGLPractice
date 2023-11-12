#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (std140) uniform Camera
{
    mat4 view;
    mat4 projection;
    vec4 position;
} camera;

uniform mat4 transform;
uniform mat3 normalMatrix;

out VS_OUT
{
    vec3 normal;
    vec2 texCoord;
    vec3 fragPos;
} vs_out;

void main()
{
    gl_Position = camera.projection * camera.view * transform * vec4(aPos, 1.0f);

    vs_out.normal = normalMatrix * aNormal;
    vs_out.texCoord = aTexCoord;
    vs_out.fragPos = vec3(transform * vec4(aPos, 1.0f));
}