#pragma once
#include "VBO.h"

class VAO
{
public:
	VAO();

	void AddVBO(const SPtr<VBO>& vbo);

	void Bind() const;
	void Unbind() const;

	static UPtr<VAO> Create() { return std::make_unique<VAO>(); }
private:
	u32 mID;
};