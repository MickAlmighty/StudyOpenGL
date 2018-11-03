#version 330 core
out vec4 color;
in vec3 pos;
in vec2 TexCoord;
uniform vec4 ourColor;
uniform sampler2D ourTexture;


void main()
{
color = texture(ourTexture, TexCoord) * ourColor;
}