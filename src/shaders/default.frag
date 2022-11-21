#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec2 texInvert = vec2(TexCoord.x, -TexCoord.y);
    FragColor = mix(texture(texture1, texInvert), texture(texture2, texInvert), 0.2);
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor.xyz, 1.0);
} 

