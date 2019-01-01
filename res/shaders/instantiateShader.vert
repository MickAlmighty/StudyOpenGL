#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 view;
uniform mat4 projection;


void main()
{
	gl_PointSize = 3;
    TexCoords = aTexCoords;    
    mat3 normalMatrix = transpose(inverse(mat3(instanceMatrix)));
    Normal = normalize(normalMatrix * aNormal);
    FragPos = vec3(instanceMatrix * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(FragPos, 1.0);
    //gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);
}