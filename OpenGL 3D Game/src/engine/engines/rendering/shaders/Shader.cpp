#include "Shader.h"

std::string ResourceLoader::LoadShader(const std::string& filename)
{
	const std::string SHADER_LOC = "res/shaders/";

	std::ifstream file;
	file.open((SHADER_LOC + filename).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);

			if (line.find("#include") == std::string::npos)
			{
				output.append(line + "\n");
			}
			else
			{
				std::string includeFile = Util::Split(line, ' ')[1];
				includeFile = includeFile.substr(1, includeFile.length() - 2);

				std::string toAppend = LoadShader(includeFile);
				output.append(toAppend + "\n");
			}
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << filename << std::endl;
	}

	return output;
}

Shader::Shader(const std::string* files, unsigned int length)
{
	program = glCreateProgram();

	shaders = new GLuint[5]{ 0 };
	counter = 0;

	if (program == 0)
	{
		std::cerr << "Program creation has failed!" << std::endl;
		exit(-1);
	}

	if (length == 1) //Compute shader
	{
		if (&files[0] == nullptr)
			return;

		if (!AddShader(files[0], COMPUTE_SHADER))
			std::cerr << "Compute shader couldn't be added";
	}
	else if (length == 2) // Vertex + fragment shader
	{
		if (&files[0] == nullptr || &files[1] == nullptr)
			return;

		if (!AddShader(files[0], VERTEX_SHADER))
			std::cerr << "Vertex shader couldn't be added";
		if (!AddShader(files[1], FRAGMENT_SHADER))
			std::cerr << "Fragment shader couldn't be added";
	}
	else if (length == 3) //Vertex + geometry + fragment shader
	{
		if (&files[0] == nullptr || &files[1] == nullptr || &files[2] == nullptr)
			return;

		if (!AddShader(files[0], VERTEX_SHADER))
			std::cerr << "Vertex shader couldn't be added";
		if (!AddShader(files[1], GEOMETRY_SHADER))
			std::cerr << "Geometry shader couldn't be added";
		if (!AddShader(files[2], FRAGMENT_SHADER))
			std::cerr << "Fragment shader couldn't be added";
	}
	else if (length == 5) //Vertex + tess control + tess evaluation + geomtry + fragment shader
	{
		if (&files[0] == nullptr || &files[1] == nullptr || &files[2] == nullptr || &files[3] == nullptr || &files[4] == nullptr)
			return;

		if (!AddShader(files[0], VERTEX_SHADER))
			std::cerr << "Vertex shader couldn't be added";
		if (!AddShader(files[1], TESSELLATION_CONTROL_SHADER))
			std::cerr << "Tessellation control shader couldn't be added";
		if (!AddShader(files[2], TESSELLATION_EVALUATION_SHADER))
			std::cerr << "Tessellation evaluation shader couldn't be added";
		if (!AddShader(files[3], GEOMETRY_SHADER))
			std::cerr << "Geometry shader couldn't be added";
		if (!AddShader(files[4], FRAGMENT_SHADER))
			std::cerr << "Fragment shader couldn't be added";
	}
}

Shader::Shader()
{
	program = glCreateProgram();

	shaders = new GLuint[5]{ 0 }; //Maximum of 5 shaders can be used - compute shader or the 5 graphics pipeline shaders
	counter = 0;

	if (program == 0)
	{
		std::cerr << "Program creation has failed!" << std::endl;
		exit(-1);
	}
}

Shader::~Shader()
{
	std::cout << "hello";
	for (unsigned int i = 0; i < counter; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::Bind() const
{
	glUseProgram(program);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

bool Shader::AddUniform(const std::string& name)
{
	GLuint location = glGetUniformLocation(program, name.c_str());

	if (location == -1)
	{
		std::cerr << "Uniform " << name << " was not found in a shader code" << std::endl;
		return false;
	}

	uniforms.emplace(name, location);
	return true;
}

bool Shader::AddUniformBlock(const std::string& name)
{
	GLuint location = glGetUniformBlockIndex(program, name.c_str());

	if (location == -1)
	{
		std::cerr << "Uniform block " << name << " was not found in a shader code" << std::endl;
		return false;
	}

	uniforms.emplace(name, location);
	return true;
}

void Shader::BindAttribute(const std::string& name, GLuint location) const
{
	glBindAttribLocation(program, location, name.c_str());
}

bool Shader::CompileShader() const
{
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLchar log[1024];
		glGetProgramInfoLog(program, 1024, NULL, log);

		fprintf(stderr, "ERROR: Linking shader program: '%s'\n", log);

		return false;
	}

	glValidateProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLchar log[1024];
		glGetProgramInfoLog(program, 1024, NULL, log);

		fprintf(stderr, "ERROR: Validating shader program: '%s'\n", log);

		return false;
	}

	return true;
}

bool Shader::AddShader(const std::string& code, ShaderType type) const
{
	switch (type)
	{
	case VERTEX_SHADER:
		return AddProgram(code, GL_VERTEX_SHADER);
	case TESSELLATION_CONTROL_SHADER:
		return AddProgram(code, GL_TESS_CONTROL_SHADER);
	case TESSELLATION_EVALUATION_SHADER:
		return AddProgram(code, GL_TESS_EVALUATION_SHADER);
	case GEOMETRY_SHADER:
		return AddProgram(code, GL_GEOMETRY_SHADER);
	case FRAGMENT_SHADER:
		return AddProgram(code, GL_FRAGMENT_SHADER);
	case COMPUTE_SHADER:
		return AddProgram(code, GL_COMPUTE_SHADER);
	default:
		std::cerr << "Invalid shader type given: " << type << std::endl;
		return false;
	}
}

bool Shader::AddProgram(const std::string& code, GLenum type) const
{
	GLuint shader = glCreateShader(type);

	shaders[counter++] = shader;

	if (shader == 0)
	{
		std::cerr << "Shader creation failed!" << std::endl;

		return false;
	}

	const GLchar* charCode[1];
	charCode[0] = code.c_str();
	GLint lengths[1];
	lengths[0] = code.length();

	glShaderSource(shader, 1, charCode, lengths);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLchar log[1024];
		glGetShaderInfoLog(shader, 1024, NULL, log);

		fprintf(stderr, "ERROR: Compiling shader type %d: '%s'\n", shader, log);

		return false;
	}

	glAttachShader(program, shader);

	return true;
}