# OpenGL Project 2: Interactive Polygon Creation

## Project Overview

This README provides a detailed overview of Project 2, an OpenGL-based project that allows interactive creation of polygons via mouse input. The project's primary objective is to enable users to click and define the vertices of a polygon, with a method of indicating when the polygon is complete, such as double-clicking, right-clicking, pressing a key, or clicking a button.

### Project Purpose

- Develop an interactive OpenGL program that facilitates the dynamic creation of polygons.
- Allow users to define the vertices by clicking on the screen.
- Implement a method (e.g., double-click, right-click, key press, button click) to signal the completion of the polygon.

### Project Details

#### Interactive Polygon Creation

Project 2 focuses on providing a user-friendly experience for creating polygons:

- Users click on the screen to define the vertices of the polygon.
- The program dynamically displays lines connecting the clicked points.
- Users can signal the completion of the polygon using a predefined action, such as double-clicking, right-clicking, pressing a key, or clicking a button.
- Upon completion, the program generates and displays the polygon based on the defined vertices.

#### OpenGL Usage

The project utilizes OpenGL functions and libraries to create a real-time rendering environment. It involves handling mouse input for defining polygon vertices and the selected method for indicating polygon completion.

### Project Implementation

To achieve the project's goals, you can follow these general steps:

1. Set up an OpenGL rendering context with the necessary libraries and tools.

2. Define and implement an interactive mechanism for capturing mouse input when users click to create vertices.

3. Dynamically render lines connecting the clicked points to provide visual feedback to the user.

4. Implement a method for signaling the completion of the polygon (e.g., double-click, right-click, key press, or button click).

5. Upon completion, generate the polygon based on the defined vertices.

6. Continuously update and render the scene in real-time.

### Building and Running the Project

To build and run the project, you will need to compile the source code (e.g., `QuestionTwo.cpp`) with the appropriate OpenGL libraries and dependencies. Ensure that you link the necessary libraries for OpenGL rendering.

Example (with g++ and GLFW):

```bash
g++ -o QuestionTwo QuestionTwo.cpp -lGL -lGLU -lglfw

