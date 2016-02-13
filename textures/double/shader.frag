#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{

   // mix the two textures
   // 0.80 of the first texture and 0.2 of the second one
   
   color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2,TexCoord), 0.2);
}
