#version 420 core // note the GLSL version!
layout (depth_greater) out float gl_FragDepth;
out vec4 color;

void main()
{             
    color = vec4(1.0f);
    gl_FragDepth = gl_FragCoord.z + 0.1f;
}  


/*
 By writing to gl_FragDepth you should take this performance penalty into consideration. From OpenGL 4.2 however, we can still sort of mediate between both sides by redeclaring the gl_FragDepth variable at the top of the fragment shader with a depth condition:


layout (depth_<condition>) out float gl_FragDepth;

This condition can take the following values:
Condition 	Description
any 	The default value. Early depth testing is disabled and you lose most performance.
greater 	You can only make the depth value larger compared to gl_FragCoord.z.
less 	You can only make the depth value smaller compared to gl_FragCoord.z.
unchanged 	If you write to gl_FragDepth, you will write exactly gl_FragCoord.z.

*/
