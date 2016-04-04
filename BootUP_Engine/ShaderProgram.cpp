#include"ShaderProgram.hpp"

#include <fstream>
#include <streambuf>
#include <vector>
#include <iostream>

void ShaderProgram::init()
{
	//initialize the shaders
	vertex = glCreateShader(GL_VERTEX_SHADER);
	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//initialize the program
	program = glCreateProgram();
}

std::string ShaderProgram::file_to_string(std::string file)
{
	std::ifstream temp(file.c_str());
	std::string string((std::istreambuf_iterator<char>(temp)), std::istreambuf_iterator<char>());

	return string;
}

ShaderProgram::ShaderProgram() 
{
	//setup the variables
	init();
}
ShaderProgram::ShaderProgram(std::string vertex_file, std::string geometry_file, std::string fragment_file)
{
	//setup the variables
	init();

	set_vertex(vertex_file);
	set_geometry(geometry_file);
	set_fragment(fragment_file);

	link();
}
ShaderProgram::~ShaderProgram() {}

void ShaderProgram::set_vertex(std::string file)
{
	std::string temp_string = file_to_string(file);
	const char* temp_file = temp_string.c_str();

	glShaderSource(vertex, 1, &temp_file, 0);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &is_compiled);
	if (is_compiled == false)
	{
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &max_length);

		std::vector <char> info_log(max_length);
		glGetShaderInfoLog(vertex, max_length, &max_length, &info_log[0]);

		std::cout << "Vertex Shader Error Log: " << std::endl << &info_log[0] << std::endl;
	}
	else
	{
		glAttachShader(program, vertex);
	}
}
void ShaderProgram::set_geometry(std::string file)
{
	std::string temp_string = file_to_string(file);
	const char* temp_file = temp_string.c_str();

	glShaderSource(geometry, 1, &temp_file, 0);
	glCompileShader(geometry);

	glGetShaderiv(geometry, GL_COMPILE_STATUS, &is_compiled);
	if (is_compiled == false)
	{
		glGetShaderiv(geometry, GL_INFO_LOG_LENGTH, &max_length);

		std::vector <char> info_log(max_length);
		glGetShaderInfoLog(geometry, max_length, &max_length, &info_log[0]);

		std::cout << "Geometry Shader Error Log: " << std::endl << &info_log[0] << std::endl;
	}
	else
	{
		glAttachShader(program, geometry);
	}
}
void ShaderProgram::set_fragment(std::string file)
{
	std::string temp_string = file_to_string(file);
	const char* temp_file = temp_string.c_str();

	glShaderSource(fragment, 1, &temp_file, 0);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &is_compiled);
	if (is_compiled == false)
	{
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &max_length);

		std::vector <char> info_log(max_length);
		glGetShaderInfoLog(fragment, max_length, &max_length, &info_log[0]);

		std::cout << "Fragment Shader Error Log: " << std::endl << &info_log[0] << std::endl;
	}
	else
	{
		glAttachShader(program, fragment);
	}
}
void ShaderProgram::link()
{
	//link the program
	glLinkProgram(program);

	//remove the shaders from the program after it's linked
	glDetachShader(program, vertex);
	glDetachShader(program, geometry);
	glDetachShader(program, fragment);
}
void ShaderProgram::use()
{
	glUseProgram(program);
}

unsigned* ShaderProgram::get_program()
{
	return &program;
}