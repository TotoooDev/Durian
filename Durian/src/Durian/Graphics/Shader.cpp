#include <pch.h>
#include <Durian/Graphics/Shader.h>
#include <GL/glew.h>

namespace Durian
{
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        std::ifstream vertexFile(vertexPath);
        std::ifstream fragmentFile(fragmentPath);

        if (!vertexFile.good())
        {
            DURIAN_LOG_ERROR("File {} does not exist!", vertexPath);
            return;
        }
        if (!fragmentFile.good())
        {
            DURIAN_LOG_ERROR("File {} does not exist!", fragmentPath);
            return;
        }

        std::stringstream vertexStream;
        std::stringstream fragmentStream;
        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        CreateFromString(vertexStream.str(), fragmentStream.str());
    }

    void Shader::CreateFromString(const std::string& vertexSource, const std::string& fragmentSource)
    {
        if (vertexSource.empty())
            DURIAN_LOG_WARN("Vertex shader is empty!");
        if (fragmentSource.empty())
            DURIAN_LOG_WARN("Fragment shader is empty!");

        const char* vertexSrc = vertexSource.c_str();
        const char* fragmentSrc = fragmentSource.c_str();

        // Compile shaders
        int success;
        char infoLog[1024];
        // Vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
        glCompileShader(vertexShader);
        // Error handling
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
            DURIAN_LOG_ERROR("Error compiling vertex shader! \n{}", infoLog);
        }
        // Fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
        glCompileShader(fragmentShader);
        // Error handling
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
            DURIAN_LOG_ERROR("Error compiling fragment shader! \n{}", infoLog);
        }

        // Shader program
        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShader);
        glAttachShader(m_ID, fragmentShader);
        glLinkProgram(m_ID);
        // Error handling
        glGetShaderiv(m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_ID, sizeof(infoLog), nullptr, infoLog);
            DURIAN_LOG_ERROR(infoLog);
        }

        // Delete shaders, we don't need them anymore
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::Bind()
    {
        glUseProgram(m_ID);
    }

    void Shader::SetInt(int value, const std::string& name)
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value); 
    }
    void Shader::SetFloat(float value, const std::string& name)
    {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value); 
    }
    void Shader::SetVec2(const glm::vec2& value, const std::string& name)
    {
        glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
    }
    void Shader::SetVec3(const glm::vec3& value, const std::string& name)
    {
        glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
    }
    void Shader::SetVec4(const glm::vec4& value, const std::string& name)
    {
        glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
    }
    void Shader::SetMat2(const glm::mat2& value, const std::string& name)
    {
        glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &value[0][0]); 
    }
    void Shader::SetMat3(const glm::mat3& value, const std::string& name)
    {
        glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &value[0][0]); 
    }
    void Shader::SetMat4(const glm::mat4& value, const std::string& name)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &value[0][0]); 
    }
}