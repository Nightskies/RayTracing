#pragma once
#include "Core/Types.h"

class VBO
{
public:
	VBO(u32 size);
	VBO(const void* data, u32 size);

	void SetData(const void* data, u32 size, u32 offset = 0);

	void Bind() const;
	void Unbind() const;

	template<typename... Args>
	static UPtr<VBO> Create(Args... args) { return std::make_unique<VBO>(std::forward<Args>(args)...); }
private:
	u32 mID;
};