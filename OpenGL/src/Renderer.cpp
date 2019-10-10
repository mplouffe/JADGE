#include "Renderer.h"

#include <iostream>

// Clear all error flags by looping glGetError until it returns no error
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
// Check the flags for errors and print the 
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}