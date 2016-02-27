#version 330 core
out vec4 color;
in vec2 TexCoords;

uniform sampler2D frontTexture;
uniform sampler2D backTexture;

void main()
{             
    if(gl_FrontFacing)
        color = texture(frontTexture, TexCoords);
    else
        color = texture(backTexture, TexCoords);
}  
