#version 400

layout(location = 0) in vec2 VertexPos;
layout(location = 1) in vec4 VertexColor;
layout(location = 2) in vec2 VertexTexCoord;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec4 Color;
out vec2 TexCoord;

void main(void)
{
	Color = VertexColor;
	TexCoord = VertexTexCoord;
	gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(vec3(VertexPos, 0), 1);
}