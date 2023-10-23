#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 position;
    uniform vec3 color;
    out vec4 fragColor;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
        fragColor = vec4(color, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    in vec4 fragColor;
    out vec4 FragColor;
    void main()
    {
        FragColor = fragColor;
    }
)";

struct Point {
    double x, y;
};

std::vector<Point> points;
bool isPolygonComplete = false;
GLuint shaderProgram;

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    if (isPolygonComplete) {
        return;
    }

    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        Point newPoint = { 2.0 * xpos / windowWidth - 1.0, 1.0 - 2.0 * ypos / windowHeight };
        points.push_back(newPoint);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ENTER) { // 'Enter' key to finalize the polygon
            isPolygonComplete = true;
        }
    }
}

int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
    // Create and compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete shaders as they are linked into the program and no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Interactive Polygon Creation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        if (isPolygonComplete) {
            glUseProgram(shaderProgram);
            GLuint vao, vbo;
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * points.size(), &points[0], GL_STATIC_DRAW);

            // Set vertex attributes
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(Point), (void*)0);

            // Set color attribute to pink (1.0, 0.5, 0.7)
            GLint colorLoc = glGetUniformLocation(shaderProgram, "color");
            glUniform3f(colorLoc, 1.0f, 0.5f, 0.7f); // Pink color

            glDrawArrays(GL_TRIANGLE_FAN, 0, points.size());
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &vbo);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
