#include "vao.h"
#include "spdlog/spdlog.h"

void VAO::Bind()
{
	spdlog::info("VAO BIND");
	glBindVertexArray(ID);
}

// Make the nothing the current Vertex Array Object
void VAO::Unbind()
{
	spdlog::info("VAO UNDBIND");
	glBindVertexArray(0);
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
	spdlog::info("ENTER LINK VAO->VBO");
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
	spdlog::info("EXIT LINK VAO->VBO");

}

VAO::VAO()
{
	//ID = GLuint();
	spdlog::info("INITIALISE VAO");
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
	//spdlog::info("Deleting Vertex Objects.");
	spdlog::info("TERMINATE VAO");
	glDeleteVertexArrays(1, &ID);
}