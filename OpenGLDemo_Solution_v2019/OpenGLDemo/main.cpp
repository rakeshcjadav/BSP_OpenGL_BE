#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

unsigned int InitTriangle();
unsigned int InitShaders();
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    //3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /*
    struct SVertex
    {
        float position[3] = { 0.5f, 0.5f, 0.0f };
        float normal[3] = { 0.0f, 0.0f, 1.0f };
    };*/

    glewInit();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
 
    unsigned int vao = InitTriangle();
    unsigned int shaderProgram = InitShaders();

    int uniformColorLocation = glGetUniformLocation(shaderProgram, "uniformColor");
    glUniform4f(uniformColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        

        int timeLocation = glGetUniformLocation(shaderProgram, "time");
        glUniform1f(timeLocation, timeValue);

        glUseProgram(shaderProgram);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

unsigned int InitTriangle()
{
    float vertices[] = {
           // 3 floats for position & 3 floats for color
           -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,    // bottom left
           0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,     // bottom right
           0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,      // top right
           -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,     // top left
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        GLuint vertexbufferObject;
        glGenBuffers(1, &vertexbufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbufferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        GLuint indexbufferObject;
        glGenBuffers(1, &indexbufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
    return VAO;
}

// Fixed function pipeline to programmable pipeline
/*
// Vertex Shader
#version 330 core
layout(location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}

// Fragment Shader
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
*/

// OpenGL 3.3 && GLSL 3.3

unsigned int InitShaders()
{
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "layout (location = 1) in vec3 color;\n"
        "out vec3 vertexcolor;\n"
        "uniform float PI;\n"
        "uniform float time;\n"
        "float angle = 25.0f * PI/180.0f;\n"
        "mat4 scaleMatrix = mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);\n"
        "mat4 translateMatrix = mat4(1.0f, 0.0f, 0.0f, 0.0f, "
                                    "0.0f, 1.0f, 0.0f, 0.0f, "
                                    "0.0f, 0.0f, 1.0f, 0.0f, "
                                    "0.0f, 0.0f, 0.0f, 1.0f);\n"
        "mat4 rotationMatrix = mat4(cos(angle),  sin(angle), 0.0f, 0.0f, "
                                    "-sin(angle), cos(angle), 0.0f, 0.0f, "
                                    "0.0f, 0.0f, 1.0f, 0.0f, "
                                    "0.0f, 0.0f, 0.0f, 1.0f);\n"
        // Order is important : Scale -> Rotate -> Translate
        "void main()\n"
        "{\n"
        "   scaleMatrix[0][0] = (sin(time) / 2.0f) + 0.5f;\n"
        "   vec4 newPos = translateMatrix * rotationMatrix * scaleMatrix * vec4(position, 1.f);\n"
        "   gl_Position = newPos;\n"
        "   vertexcolor = color;\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 vertexcolor;\n"
        "uniform vec4 uniformColor;\n"
        "uniform float time;\n"
        "void main()\n"
        "{\n"
        "    //FragColor = vec4(1.0f, 1.0f, vertexcolor.gr);\n"
        "    FragColor = vec4((sin(time) / 2.0f) + 0.5f, vertexcolor.bg, 1.0f);\n"
        "}\0";
    int success;

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }
    return shaderProgram;
}