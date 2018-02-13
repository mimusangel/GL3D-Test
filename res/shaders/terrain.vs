#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fColor;

void main()
{
    vec4 worldPosition = model * vec4(vertexPosition, 1);
    gl_Position = projection * view * worldPosition;
    fColor = vertexColor;
}