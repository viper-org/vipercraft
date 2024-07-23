#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

out vec4 Color;

uniform mat4 ortho;

void main()
{
    gl_Position = ortho * vec4(aPos, 0.0f, 1.0f);
    Color = aColor;
}