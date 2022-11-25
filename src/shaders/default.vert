#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in float a_TexId;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexId;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(a_Pos, 1.0);
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexId = a_TexId;
}
