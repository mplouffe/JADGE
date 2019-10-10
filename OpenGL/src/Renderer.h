#pragma once

#include <GL/glew.h>

// GL ERROR CHECKING USING GET ERROR
// This is for compatibility with version of OpenGL < 4.3
// Assert Macro
#define ASSERT(x) if (!(x)) __debugbreak();
// GLCall Macro
// Just wraps the function call in call/clear error wrappers
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);