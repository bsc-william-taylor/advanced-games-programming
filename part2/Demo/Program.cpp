
#include "Program.h"

Program::Program()
    : compiled(GL_TRUE)
{
    programID = glCreateProgram();
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    vertexID = glCreateShader(GL_VERTEX_SHADER);
}

Program::~Program()
{
    glDeleteProgram(programID);
    glDeleteShader(fragmentID);
    glDeleteShader(vertexID);
}

void Program::setFragmentSource(const char * source)
{
    if (std::string(source).find(".glsl") == std::string::npos)
    {
        glShaderSource(fragmentID, 1, &source, NULL);
        glCompileShader(fragmentID);
    }
    else
    {
        std::ifstream file(source);
        if (file.is_open())
        {
            std::string src = SHADER_VERSION;
            while (!file.eof())
            {
                std::string line = "";
                std::getline(file, line);
                src += line;
            }

            const GLchar * c_source = src.c_str();
            glShaderSource(fragmentID, 1, &c_source, NULL);
            glCompileShader(fragmentID);
        }
        else
        {
            std::cout << "Error opening file " << source << std::endl;
        }
    }

    GLint isCompiled = 0;
    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        compiled = GL_FALSE;
        glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &maxLength);
        GLchar* errorLog = new char[maxLength];
        glGetShaderInfoLog(fragmentID, maxLength, &maxLength, &errorLog[0]);
        printf(errorLog);
    }
}

void Program::setVertexSource(const char * source)
{
    if (std::string(source).find(".glsl") == std::string::npos)
    {
        glShaderSource(vertexID, 1, &source, NULL);
        glCompileShader(vertexID);
    }
    else
    {
        std::ifstream file(source);
        if (file.is_open())
        {
            std::string src = SHADER_VERSION;
            while (!file.eof())
            {
                std::string line = "";
                std::getline(file, line);
                src += line;
            }

            const GLchar* c_source = src.c_str();
            glShaderSourceARB(vertexID, 1, &c_source, NULL);
            glCompileShader(vertexID);
        }
        else
        {
            std::cout << "Error opening file " << source << std::endl;
        }
    }

    GLint isCompiled = 0;
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        compiled = GL_FALSE;
        glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &maxLength);

        GLchar * errorLog = new char[maxLength];
        glGetShaderInfoLog(vertexID, maxLength, &maxLength, &errorLog[0]);
        printf(errorLog);
    }
}

GLboolean Program::compile()
{
    if (compiled == GL_TRUE)
    {
        glAttachShader(programID, vertexID);
        glAttachShader(programID, fragmentID);
        glLinkProgram(programID);
    }

    return compiled;
}

GLvoid Program::setVector(GLchar * nm, glm::vec2 v)
{
    GLuint ID = glGetUniformLocation(programID, nm);
    glUniform2fv(ID, 1, glm::value_ptr(v));
}

void Program::setMatrix(GLchar* nm, float * m)
{
    GLuint ID = glGetUniformLocation(programID, nm);
    glUniformMatrix4fv(ID, 1, GL_FALSE, m);
}

void Program::bind(GLuint textureID)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

GLvoid Program::setInteger(GLchar * nm, int v)
{
    GLuint ID = glGetUniformLocation(programID, nm);
    glUniform1i(ID, v);
}

void Program::prepare(GLuint objectID)
{
    glBindVertexArray(objectID);
}

void Program::bindShader()
{
    glUseProgram(programID);
}

void Program::run(GLuint type, GLuint start, GLuint count)
{
    glDrawArrays(type, start, count);
}

void Program::run(GLuint start, GLuint count)
{
    run(GL_TRIANGLES, start, count);
}

void Program::run(GLuint count)
{
    run(GL_TRIANGLES, 0, count);
}

GLuint Program::getID()
{
    return programID;
}

void Program::unbindShader()
{
    glUseProgram(NULL);
}
