#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float LightIntensity;
in float Transparency;

uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture, TexCoord) * vec4(LightIntensity, LightIntensity, LightIntensity, Transparency);
}