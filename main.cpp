#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version you are using (we are using Version 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // First "3" of version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Second "3" of version 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Tell GLFW we are using Core profile (vs. compatibility profile that has outdated commands to be back-compatible)

	// create a window object with GLFW window datatype with a size of 800x800 pixels named "OpenGL Tutorial"
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Tutorial", NULL, NULL); // datatype* (width, height, name, fullscreen?, not important)

	//check to see if the window had an error generating (and if it does close it)
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}
	//tell GL to use the window we created (load the window into the current context; open the window)
	glfwMakeContextCurrent(window);

	// Load glad into OpenGL
	gladLoadGL();

	glViewport(0,0, 800,800); // area of OpenGL we want to render in from an (x, y) of (0, 0) to (800, 800)

	glClearColor(1.0f, 0.4f, 0.0f, 1.0f); //Orange; prepare to clear color and replace it (color back buffer)
	glClear(GL_COLOR_BUFFER_BIT); // configure buffer swap for color buffer
	glfwSwapBuffers(window); // swap buffer (change the color!)



	// Keep the window open unless the close button is pressed or something else closes the window
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents(); // process events sent to the window like resizing or clicking or window changes
	}

	// delete the window when we are done with it
	glfwDestroyWindow(window);

	//end OpenGL when we are done with the program
	glfwTerminate();
	return 0;
}