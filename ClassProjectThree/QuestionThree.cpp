#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
GLint colorLoc;
bool isTranslationMode = false;
bool isRotationMode = false;
bool isScaleMode = false;
double translationDelta = 0.01;
double rotationDelta = 5.0; // Degrees
double scaleFactor = 1.0; // Initial scale factor

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
        else if (key == GLFW_KEY_T) { // 'T' key for translation mode
            isTranslationMode = true;
            isRotationMode = false;
            isScaleMode = false;
        }
        else if (key == GLFW_KEY_R) { // 'R' key for rotation mode
            isTranslationMode = false;
            isRotationMode = true;
            isScaleMode = false;
        }
        else if (key == GLFW_KEY_S) { // 'S' key for scaling mode
            isScaleMode = true;
            isTranslationMode = false;
            isRotationMode = false;
        }
        else if (key == GLFW_KEY_MINUS) { // '-' key to decrease the scale
            if (isScaleMode) {
                scaleFactor *= 0.9; // Adjust the scaling factor
            }
        }
        else if (key == GLFW_KEY_EQUAL) { // '+' key to increase the scale
            if (isScaleMode) {
                scaleFactor *= 1.1; // Adjust the scaling factor
            }
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

    colorLoc = glGetUniformLocation(shaderProgram, "color");

    return shaderProgram;
}

void renderPolygon() {
    glUseProgram(shaderProgram);
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Apply scaling transformation to each point
    std::vector<Point> scaledPoints;
    for (const Point& point : points) {
        scaledPoints.push_back({ point.x * scaleFactor, point.y * scaleFactor });
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * scaledPoints.size(), &scaledPoints[0], GL_STATIC_DRAW);

    // Set vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(Point), (void*)0);

    glUniform3f(colorLoc, 1.0f, 0.5f, 0.7f); // Pink color

    glDrawArrays(GL_TRIANGLE_FAN, 0, scaledPoints.size());
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void translatePolygon(double tx, double ty) {
    for (Point& point : points) {
        point.x += tx;
        point.y += ty;
    }
}

void rotatePolygon(double angleDegrees) {
    double angleRadians = angleDegrees * M_PI / 180.0;
    double cosA = cos(angleRadians);
    double sinA = sin(angleRadians);
    for (Point& point : points) {
        double x = point.x;
        double y = point.y;
        point.x = x * cosA - y * sinA;
        point.y = x * sinA + y * cosA;
    }
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Interactive Transformation of Polygons", NULL, NULL);
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
            renderPolygon();
        }

        if (isTranslationMode) {
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
                translatePolygon(0.0, translationDelta);
            }
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
                translatePolygon(0.0, -translationDelta);
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                translatePolygon(-translationDelta, 0.0);
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                translatePolygon(translationDelta, 0.0);
            }
        }

        if (isRotationMode) {
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                rotatePolygon(rotationDelta);
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                rotatePolygon(-rotationDelta);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
