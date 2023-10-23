#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
uniform vec3 color;
void main() {
    FragColor = vec4(color, 1.0);
}
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW to not create an OpenGL context on its own
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set the OpenGL viewport size
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    // Set a callback for when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Create and compile shaders
    unsigned int vertexShader, fragmentShader, shaderProgram;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Set up vertex data for rectangle, square, lines, and points
    float vertices[] = {
        // Rectangle (4 vertices)
        -0.4f, -0.4f,
        0.4f, -0.4f,
        0.4f, 0.2f,
        -0.4f, 0.2f,

        // Square (4 vertices)
        -0.8f, -0.8f,
        -0.6f, -0.8f,
        -0.6f, -0.6f,
        -0.8f, -0.6f,

        // Line 1 (thick, red)
        -0.7f, -0.5f,
        -0.2f, -0.5f,
        // Line 2 (dashed, blue)
        0.2f, -0.5f,
        0.7f, -0.5f,

        // Point 1 (magenta)
        -0.7f, 0.5f,
        // Point 2 (cyan)
        0.7f, 0.5f
    };

    // Set up VBO and VAO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Draw the rectangle (green)
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 0.0f, 1.0f, 0.0f); // Green
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // Draw the square (blue)
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 0.0f, 0.0f, 1.0f); // Blue
        glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

        // Draw Line 1 (thick, red)
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 0.0f, 0.0f); // Red
        glLineWidth(5.0f);  // Thick line
        glDrawArrays(GL_LINES, 8, 2);

        // Draw Line 2 (dashed, blue)
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 0.0f, 0.0f, 1.0f); // Blue
        // Implement a dashed line using the fragment shader
        glDrawArrays(GL_LINES, 10, 2);

        // Draw Point 1 (magenta)
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 0.0f, 1.0f); // Magenta
        glPointSize(10.0f);  // Larger point
        glDrawArrays(GL_POINTS, 12, 1);

        // Draw Point 2 (cyan)
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 0.0f, 1.0f, 1.0f); // Cyan
        glPointSize(15.0f);  // Even larger point
        glDrawArrays(GL_POINTS, 13, 1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up and exit
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
