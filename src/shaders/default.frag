#version 330 core

out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexId;

uniform sampler2D texture_1;

void main()
{
	if(v_TexId > 0)
	{
		FragColor = texture(texture_1, v_TexCoord) * v_Color;
	}
	else
	{
		FragColor = v_Color;
	}
} 

