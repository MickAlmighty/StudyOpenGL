#version 330 core
	layout(location = 0) in vec3 position;
	layout (location = 1) in vec2 texCoord;
	
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
	
	out vec3 pos;
	out vec2 TexCoord;
	
	void main()
	{
	TexCoord = texCoord;
	pos = vec3(position.x, position.y, position.z);
	gl_Position =  projection * view * model * vec4(position, 1.0f);
	}