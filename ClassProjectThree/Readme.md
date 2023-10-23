# OpenGL Project 3: Interactive Polygon Transformation

## Project Overview

This README provides a detailed overview of Project 3, an OpenGL-based project that allows interactive translation, rotation, and scaling of polygons via user input. The project can be implemented either as a standalone program or as an extension to a previous project. It provides two modes of interaction: keyboard input for precise transformations and mouse input with a mode select for dynamic manipulation.

### Project Purpose

- Develop an OpenGL program that enables users to interactively transform polygons using translation, rotation, and scaling.
- Provide two modes of interaction: keyboard input for precise transformations and mouse input with a mode select for dynamic manipulation.

### Project Details

#### Interactive Polygon Transformation

Project 3 focuses on allowing users to perform the following transformations on polygons:

1. **Translation**: Move the polygon by a specified amount. Users can control the translation through arrow keys (keyboard input) or by dragging the polygon with the mouse (mouse input).

2. **Rotation**: Rotate the polygon around its center by a specified angle. This can be achieved through keyboard input.

3. **Scaling**: Resize the polygon uniformly in both the X and Y dimensions. Scaling can also be controlled through keyboard input.

#### Implementation Options

- **Standalone Program**: You can develop this project as a standalone program with its user interface and interaction methods.

- **Extension to Previous Project**: Alternatively, you can extend the functionality of a previous project to include interactive transformation features.

#### OpenGL Usage

The project will utilize OpenGL functions and libraries to create an interactive rendering environment. It involves handling user input for translation, rotation, and scaling of polygons.

### Project Implementation

To achieve the project's goals, you can follow these general steps:

1. Set up an OpenGL rendering context with the necessary libraries and tools.

2. Define and create the polygons you want to transform.

3. Implement two modes of interaction: keyboard input and mouse input with mode selection.

4. In keyboard input mode:
   - Use arrow keys for translation.
   - Implement rotations and scaling using the keyboard.

5. In mouse input mode:
   - Switch between translation, rotation, and scaling modes using a specific key (e.g., 't' for translation).
   - Drag the polygon with the mouse to perform transformations.

6. Continuously update and render the scene to provide real-time feedback.

### Building and Running the Project

To build and run the project, you will need to compile the source code (e.g., `QuestionThree.cpp`) with the appropriate OpenGL libraries and dependencies. Ensure that you link the necessary libraries for OpenGL rendering.

Example (with g++ and GLFW):

```bash
g++ -o QuestionThree QuestionThree.cpp -lGL -lGLU -lglfw

