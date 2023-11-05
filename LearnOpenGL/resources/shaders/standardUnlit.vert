#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (std140) uniform Camera
{
    mat4 view;
    mat4 projection;
};

uniform mat4 transform;

out vec3 vertexColor;
out vec3 normal;
out vec2 texCoord;

void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0f);
    normal = aNormal;
    texCoord = aTexCoord;
}