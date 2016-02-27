#version 330 core
out vec4 color;

in VS_OUT
{
    vec2 TexCoords;
} fs_in;

uniform sampler2D texture;

void main()
{             
    color = texture(texture, fs_in.TexCoords);   
} 
