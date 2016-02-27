
GLfloat quadVertices[] = {
    // Positions     // Colors
    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
     0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
    -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
     0.05f, -0.05f,  0.0f, 1.0f, 0.0f,   
     0.05f,  0.05f,  0.0f, 1.0f, 1.0f		    		
};  


//offset positions:

glm::vec2 translations[100];
int index = 0;
GLfloat offset = 0.1f;
for(GLint y = -10; y < 10; y += 2)
{
    for(GLint x = -10; x < 10; x += 2)
    {
        glm::vec2 translation;
        translation.x = (GLfloat)x / 10.0f + offset;
        translation.y = (GLfloat)y / 10.0f + offset;
        translations[index++] = translation;
    }
}  

//draw

shader.Use();
for(GLuint i = 0; i < 100; i++)
{
    stringstream ss;
    string index;
    ss << i; 
    index = ss.str(); 
    GLint location = glGetUniformLocation(shader.Program, ("offsets[" + index + "]").c_str())
    glUniform2f(location, translations[i].x, translations[i].y);
}  

//draw the squares

glBindVertexArray(quadVAO);
glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);  
glBindVertexArray(0);
