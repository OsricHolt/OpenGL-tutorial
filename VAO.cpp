#include "VAO.h"

// Constructor that generates a VAO ID
VAO::VAO() {
	glGenVertexArrays(1, &ID); //MUST generate VAO BEFORE VBO
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO VBO, GLuint layout) {
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//how to read VBO (vertex attribute index, values per vertex, value type, interger coordinates?, vertex stride(how much data between verteces, offset)
	glEnableVertexAttribArray(layout); //enable array (position of vertex attribute)
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind() {
	glBindVertexArray(ID); //select vertex array for VBO
}

// Unbinds the VAO
void VAO::Unbind() {
	glBindVertexArray(0); //clear bind to avoid accidents
}

// Deletes the VAO
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);

}