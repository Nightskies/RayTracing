#include "VAO.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

VAO::VAO()
{
	glCreateVertexArrays(1, &mID);
}

void VAO::AddVBO(const SPtr<VBO>& vbo)
{
	glBindVertexArray(mID);
	vbo->Bind();

	// Pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), reinterpret_cast <const void*>(0));

	// Color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), reinterpret_cast<const void*>(sizeof(glm::vec3)));

}

void VAO::Bind() const
{
	glBindVertexArray(mID);
}

void VAO::Unbind() const
{
	glBindVertexArray(0);
}