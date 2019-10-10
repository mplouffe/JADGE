#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>	// for parsing the shader
#include <sstream>  // string stream to add the parsed shader lines to a buffer as read in

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

// create structure to return both source types as strings in a single object
// cherno method of returning multiple things in a single method
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

// ParseShader
// parses the shader filepath into two separate strings
// returns a ShaderProgramSource as defined above
static ShaderProgramSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);			// getting stream from the shader file

	enum class ShaderType
	{
		// enum value also serves as index into the source string array when
		// adding lines to the source strings
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	// PARSING THROUG THE FILE
	std::string line;						// to hold current line from stream
	std::stringstream ss[2];				// an array of string streams to hold the parsed lines from the shader file
	ShaderType type = ShaderType::NONE;		// type of the shader being parsed; serves as index into ss for adding lines to the stream
	// cycle through the stream line by line
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)		// if line is shader tag
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX; // set mode to vertex
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT; // set mode to fragment
		}
		else												// if it's not a shader tag, add it to the stream
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); // source string must still exist when called here
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// errorhandling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		// get the error message
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char)); // the way to do char message[length];
		glGetShaderInfoLog(id, length, &length, message);
		
		// output the error message
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<" shader!" << std::endl;
		std::cout << message << std::endl;
		
		// delete the shader the return 0 cause error
		glDeleteShader(id);
		return 0;
	}

	// return success
	return id;

}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	// WRITE ONCE and done
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// setting open gl to version 3.3 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);								// should synchronize with our vsync

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;  // outputting the version to console

	// list of vertex positions
	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	// setting up index buffer
	unsigned int indicies[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Setting up and binding the VERTEX ARRAY OBJECT
	// Step 1: Binding the vertex array object
	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	// Setting up and binding the VERTEX BUFFER DATA to the VERTEX ARRAY OBJECT
	// Step 1: the buffer
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	// Setting up and binding the VERTEX ATTRIUTES to the VERTEX ARRAY OBJECT
	// Step 2: the vertex attributes
	//specifying a single attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);					// this is the call that links the currently bound buffer to the vao
	glEnableVertexAttribArray(0);				// enabled the vertex attrib array

	// Setting up and binding the INDEX BUFFER OBJECT
	// Step 1: the index buffer object
	IndexBuffer ib(indicies, 6);




	// CREATING SHADER
	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");			// creating shader via parse method above
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);	// creating shader via creae shader method above
	glUseProgram(shader);		// attaching the shader


	// un-binding
	// to simulate more complex rendering with mulitple buffers and settings
	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// end un-binding



	// USING A UNIFORM IN A SHADER
	// setting up the uniform
	int location = glGetUniformLocation(shader, "u_Color");		// get the location of the uniform in memory
	ASSERT(location != -1);										// make sure you find the uniform
	// variables to animate the color
	float r = 0.0f;
	float increment = 0.05f;


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shader);														// 1 bind shader
		glUniform4f(location, r, 0.3f, 0.8f, 1.0f);									// 2 set up uniforms (set the value of the uniform by passing in the location returned from glGetUniformLocation above)

		// glBindBuffer(GL_ARRAY_BUFFER, buffer);										// 3 bind vertex buffer								// handled by vao
		// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);		// 4 set up layout of vertex buffer					// handled by vao
		// glEnableVertexAttribArray(0);												//   [cont] enabled the vertex attrib array

		glBindVertexArray(vao);														// 3 & 4 handled
		ib.Bind();																	// 5 bind index buffer

		// Draw the elements using the index(aka element) buffer
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));			// 6 call draw elements

		// simple logic to animate the color
		if (r > 1.0f || r < 0.0f)
		{
			increment *= -1;
		}
		r += increment;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// cleaning up at end of the program
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}