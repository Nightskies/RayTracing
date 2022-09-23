#include "VBO.h"

#include <glad/glad.h>

VBO::VBO(u32 size)
{
	glCreateBuffers(1, &mID);
	glBindBuffer(GL_ARRAY_BUFFER, mID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VBO::VBO(const void* data, u32 size)
{
	glCreateBuffers(1, &mID);
	glBindBuffer(GL_ARRAY_BUFFER, mID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VBO::SetData(const void* data, u32 size, u32 offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, mID);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mID);
}

void VBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
