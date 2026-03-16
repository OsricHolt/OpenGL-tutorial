#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() {
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version you are using (we are using Version 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // First "3" of version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Second "3" of version 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Tell GLFW we are using Core profile (vs. compatibility profile that has outdated commands to be back-compatible)

	// Vertex coordinates
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // bottom left vertex
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // bottom right vertex
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // top middle vertex
	}; // define the vertices of a triangle

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

	// Create vertex shader (object to send vertices to GPU) and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //generate shader object and get its reference value (returns address of shader)
	// attach vertex shader source to vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // (reference value, # of strings for shader, source code, NULL)
	glCompileShader(vertexShader); // compiles source code into machine code so GPU can understand

	// Create fragment shader (object to connect vertices to GPU) and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //generate fragment shader and get its reference value
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);// (reference value, # of strings for shader, source code, NULL)
	glCompileShader(fragmentShader); // compiles source code into machine code so GPU can understand

	//must "wrap up" shaders into a shader program to use them
	GLuint shaderProgram = glCreateProgram(); //generates shader program (only 1 type of shader program)

	glAttachShader(shaderProgram, vertexShader); //attach vertex shader to program
	glAttachShader(shaderProgram, fragmentShader); //attach fragment shader to program
	glLinkProgram(shaderProgram); // takes program ingredients and "wraps" them up (sorta like compiling program)

	glDeleteShader(vertexShader); // now that shaders are "wrapped up", we clear the space they were using
	glDeleteShader(fragmentShader); // now that shaders are "wrapped up", we clear the space they were using



	// Now we send buffers (different from last lesson) to GPU from CPU (we want big batches for efficiency since slow)
	GLuint VAO, VBO; //Vertex Buffer Object (VBO); usually an array of objects, but we only have one
	//Vertex Array Object (VAO) points to buffers

	glGenVertexArrays(1, &VAO); //MUST generate VAO BEFORE VBO
	glGenBuffers(1, &VBO); // generate buffers (1 object, address of array of objects)
	//binding is like selecting a target; firing a function that modifies bound object's type modifies the current object
	glBindVertexArray(VAO); //select vertex array for VBO

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //GL_ARRAY_BUFFER is vertex buffer type
	//store our vertices in the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// STREAM - modify once, use few times; STATIC - use once, use many times; DYNAMIC - modify many times, used many times
	//DRAW - vertices modify and used to draw;READ - get shader/buffer data; COPY - transfer data between buffers

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//how to read VBO (vertex attribute index, values per vertex, value type, interger coordinates?, vertex stride(how much data between verteces, offset)
	glEnableVertexAttribArray(0); //enable array (position of vertex attribute)

	glBindBuffer(GL_ARRAY_BUFFER, 0); //clear bind to avoid accidents
	glBindVertexArray(0); //clear bind to avoid accidents




	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Navy Blue; prepare to clear color and replace it (color back buffer)
	glClear(GL_COLOR_BUFFER_BIT); // configure buffer swap for color buffer
	glfwSwapBuffers(window); // swap buffer (change the color!)



	// Keep the window open unless the close button is pressed or something else closes the window
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Navy Blue; prepare to clear color and replace it (color back buffer)
		glClear(GL_COLOR_BUFFER_BIT); // configure buffer swap for color buffer
		glUseProgram(shaderProgram); //select shader program
		glBindVertexArray(VAO); // select vertex array (like pointing to vertex buffer
		glDrawArrays(GL_TRIANGLES, 0, 3); //drawing function; (type of primitive, vertex starting index, amount of vertices)
		glfwSwapBuffers(window); // swap buffer (display triangle!)


		glfwPollEvents(); // process events sent to the window like resizing or clicking or window changes
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// delete the window when we are done with it
	glfwDestroyWindow(window);

	//end OpenGL when we are done with the program
	glfwTerminate();
	return 0;
}