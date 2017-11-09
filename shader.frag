#version 400

in vec2 TexCoord;
in vec4 Color;

uniform bool usingTextures;
uniform sampler2D Tex;

layout(location = 0) out vec4 FragColor;

void main(void)
{
	if (usingTextures)
	{
		FragColor = texture(Tex, TexCoord);
	}
	else
	{
		FragColor = Color;
	}
}