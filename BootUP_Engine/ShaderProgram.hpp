#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <glew/glew.h>
#include <string>

class ShaderProgram
{
private:
	GLuint vertex, geometry, fragment, program;
	GLint is_compiled, max_length;

	std::string file_to_string(std::string file);

	void init();

public:
	ShaderProgram();
	ShaderProgram(std::string vertex_file, std::string geometry_file, std::string fragment_file);
	~ShaderProgram();

	void set_vertex(std::string file);
	void set_geometry(std::string file);
	void set_fragment(std::string file);
	void link();
	void use();

	unsigned* get_program();
};

#endif//SHADER_PROGRAM