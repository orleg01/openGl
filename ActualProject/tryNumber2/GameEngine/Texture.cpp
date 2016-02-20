#include "Texture.h"

std::vector<Texture*> Texture::allTexture;

Texture::~Texture()
{
}

Texture * Texture::getTexture(string path , glm::vec2 textureWarpOption)
{
	for (Texture* texture : allTexture)
	{
		if (texture->path.compare(path) == 0)
		{
			if(textureWarpOption == texture->textureWarpOption)
				return texture;
		}
	}
	return new Texture(path , textureWarpOption);
}

void Texture::setTexturesToShader(vector<Texture*> myTextures[] , GLuint shadId)
{
	int numberOfItems = 0;
	for (int i = 0; i < aiTextureType_UNKNOWN + 1; i++)
	{
		for (int j = 0; j < myTextures[i].size() ; j++)
		{
			glActiveTexture(GL_TEXTURE0 + numberOfItems);
			glBindTexture(GL_TEXTURE_2D, myTextures[i][j]->textureId);
			stringstream tempStr;
			tempStr << myTextures[i][j]->nameOfTexture << "Texture" << j;
			glUniform1i(glGetUniformLocation(shadId, tempStr.str().c_str() ) , numberOfItems++);
		}
	}
}

void Texture::unBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, this->textureId);
}

void Texture::deleteAllTextures()
{
	for (int i = 0; i < allTexture.size(); i++)
	{
		delete allTexture[i];
	}
}

int getHowToRepeatTexture(int number) 
{
	switch (number)
	{
	case aiTextureMapMode_Clamp:
		return GL_CLAMP_TO_EDGE;
		break;
	case aiTextureMapMode_Decal:
		return GL_CLAMP_TO_BORDER;
		break;
	case aiTextureMapMode_Wrap:
		return GL_REPEAT;
		break;
	default:
		return GL_MIRRORED_REPEAT;
		break;
	}
}

Texture::Texture(string path , glm::vec2 textureWarpOption)
{
	this->textureWarpOption = textureWarpOption;
	glGenTextures(1, &this->textureId);
	glBindTexture(GL_TEXTURE_2D, this->textureId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getHowToRepeatTexture(textureWarpOption.x));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getHowToRepeatTexture(textureWarpOption.y));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	unBind();
}