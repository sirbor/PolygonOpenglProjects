# OpenGL Project 1: Drawing Graphic Elements

## Project Overview

This README provides a detailed overview of Project 1, an OpenGL-based project focused on drawing various graphic elements with distinct attributes. The project's primary objective is to create a visually appealing image that includes a combination of lines, polygons, and points, each with unique characteristics.

### Project Purpose

- Demonstrate the use of OpenGL to create and render graphical elements.
- Showcase the versatility of OpenGL by applying different attributes to lines, polygons, and points.
- Develop a visually engaging image by combining a variety of graphical elements.

### Project Details

#### Graphic Elements

Project 1 aims to include the following graphic elements in the rendered image:

1. **Lines (At least 2)**:
   - The lines should have different attributes such as color, thickness (dashed vs. thick lines), and style.

2. **Polygons (At least 2)**:
   - Create two polygons with different attributes, which can include variations in color, fill patterns, and shapes.

3. **Points (At least 2)**:
   - Render two points, each with distinct attributes, such as color and size.

#### OpenGL Usage

In this project, you will utilize OpenGL functions and libraries to create and render the graphic elements. You will define the attributes for each element, such as color, size, and style, within the OpenGL rendering context.

### Project Implementation

To achieve the project's goals, you can follow these general steps:

1. Set up an OpenGL rendering context using the necessary libraries and tools.

2. Define and create the graphic elements: lines, polygons, and points.

3. Apply different attributes to each element. For example, you can set various colors, thickness, fill patterns, and styles.

4. Ensure the correct positioning and arrangement of the graphic elements to create a visually appealing image.

5. Render the scene and display the image.

6. Test and refine the attributes and arrangement as needed to achieve the desired visual result.

### Building and Running the Project

To build and run the project, you will need to compile the source code (e.g., `QuestionOne.cpp`) with the appropriate OpenGL libraries and dependencies. Ensure that you link the necessary libraries for OpenGL rendering.

Example (with g++ and GLFW):

```bash
g++ -o QuestionOne QuestionOne.cpp -lGL -lGLU -lglfw

