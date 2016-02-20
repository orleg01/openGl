#include "Shader.h"

vector<Shader*> Shader::allShader;

Shader* Shader::GetShader(Material* mat, Mesh* mesh)
{
	ShaderParam shadPar = InitializeStruct(mat, mesh);
	for (Shader* shad : allShader)
	{
		if (shad->shadStructParam == shadPar)
			return shad;
	}
	return new Shader(mat, mesh, shadPar);
}

GLuint Shader::getShaderId()
{
	return this->shaderId;
}

VertexShaderVersion Shader::getVertexVersion(ShaderParam* shadParam)
{
	if (*shadParam == ShaderParam())
		return BASIC_VS_VER;
}

FragmentShaderVersion Shader::getFragmentVersion(ShaderParam * shadParam)
{
	if (*shadParam == ShaderParam())
		return BASIC_FS_VER;
}

void Shader::UseShader()
{
	glUseProgram(this->shaderId);
}

void CheckShaderCompile(GLuint shadMinorId , char* name , int enumToDelever) 
{
	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shadMinorId, enumToDelever, &success);
	if (!success)
	{
		glGetShaderInfoLog(shadMinorId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::"<< name <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

Shader::Shader(Material* mat, Mesh* mesh, ShaderParam shadeStruct)
{
	GLuint vertex;
	GLuint fragment;

	VertexShaderVersion vertVersion = getVertexVersion(&shadeStruct);
	stringstream verShader;
	{
		verShader << VERSION_OF_SHADER << POSITION_OF_VERTEX << MATRIXES_OF_LOCATION;

		switch (vertVersion)
		{

		}

		verShader << OPEN_MAIN_FUNCTION << CALCULATE_LOCATION_OF_VERTEX;

		switch (vertVersion)
		{

		}

		verShader << CLOSE_FUNCTION;
	}

	std::cout << verShader.str().c_str();

	FragmentShaderVersion fragVer = getFragmentVersion(&shadeStruct);
	stringstream fragShader;
	{
		fragShader << VERSION_OF_SHADER << FINAL_COLOR;
		switch (fragVer)
		{
		case BASIC_FS_VER:
			fragShader << UNIFORM_COLOR_FOR_WHOLE_OBJECT;
			break;
		}

		fragShader << OPEN_MAIN_FUNCTION;
		switch (fragVer)
		{
		case BASIC_FS_VER:
			fragShader << "color = vec4(colorForObject , 1);\n";
			break;
		}
		fragShader << CLOSE_FUNCTION;
	}

	std::cout << fragShader.str().c_str();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	{
		string tempChar = verShader.str();
		const char* charsTemp = tempChar.c_str();
		glShaderSource(vertex, 1, &charsTemp, NULL);
		glCompileShader(vertex);
		CheckShaderCompile(vertex, "VERTEX" , (int)GL_COMPILE_STATUS);
	}
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	{
		string tempChar = fragShader.str();
		const char* charsTemp = tempChar.c_str();
		glShaderSource(fragment, 1, &charsTemp, NULL);
		glCompileShader(fragment);
		CheckShaderCompile(fragment, "FRAGMENT", (int)GL_COMPILE_STATUS);
	}

	this->shaderId = glCreateProgram();
	{
		glAttachShader(this->shaderId, vertex);
		glAttachShader(this->shaderId, fragment);
		glLinkProgram(this->shaderId);
		CheckShaderCompile(shaderId, "PROGRAM", (int)GL_LINK_STATUS);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}



ShaderParam InitializeStruct(Material* mat, Mesh* mesh)
{
	ShaderParam structToReturn;

	structToReturn.diffuseColor = mat->allTextureOfMaterial[aiTextureType_DIFFUSE].size() == 0;
	structToReturn.specularColor = mat->allTextureOfMaterial[aiTextureType_SPECULAR].size() == 0;
	structToReturn.ambientColor = mat->allTextureOfMaterial[aiTextureType_AMBIENT].size() == 0;
	structToReturn.emissiveColor = mat->allTextureOfMaterial[aiTextureType_EMISSIVE].size() == 0;
	structToReturn.opacity = mat->allTextureOfMaterial[aiTextureType_OPACITY].size() == 0;
	structToReturn.shininess = mat->allTextureOfMaterial[aiTextureType_SHININESS].size() == 0;
	structToReturn.refracti = mat->allTextureOfMaterial[aiTextureType_REFLECTION].size() == 0;
	
	ENTER_NUMBER_OF_ITEMS_IN_VECTOR(structToReturn.numberOfstengthOfTexture, mat->stengthOfTexture);
	ENTER_NUMBER_OF_ITEMS_IN_VECTOR(structToReturn.numberOfWhichOperationPreform, mat->whichOperationPreform);
	ENTER_NUMBER_OF_ITEMS_IN_VECTOR(structToReturn.numberOfMapping, mat->mapping);
	ENTER_NUMBER_OF_ITEMS_IN_VECTOR(structToReturn.numberOfUvwsrc , mat->uvwsrc);
	ENTER_NUMBER_OF_ITEMS_IN_VECTOR(structToReturn.numberOfTexFlag , mat->texFlag);

	structToReturn.useUV = mesh->UseUVs();
	structToReturn.useNormals = mesh->UseNormals();
	structToReturn.useTangens = mesh->UseTangens();
	structToReturn.useColors = mesh->UseColors();

	return structToReturn;
}

