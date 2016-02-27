glEnable(GL_PROGRAM_POINT_SIZE);  

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);    
    gl_PointSize = gl_Position.z;    
}  
