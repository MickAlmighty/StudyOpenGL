#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D texture_diffuse1;
uniform bool isFromFile;
void main()
{    
	if(isFromFile)
		FragColor = texture(texture_diffuse1, TexCoords);
	else
		FragColor = vec4(1,0,1,1);
	}