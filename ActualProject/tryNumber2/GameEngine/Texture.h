
#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <assimps\assimp\material.h>
#include <glew\GL\glew.h>
#include <glfw/GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <soil\SOIL.h>
#include <glm\glm.hpp>

//my Headers
class Texture;

using namespace std;

class Texture
{
public:
	~Texture();
	static Texture* getTexture(string path , glm::vec2 textureWarpOption);
	static void setTexturesToShader(vector<Texture*> myTextures[] , GLuint shadId);

	void unBind();
	void Bind();
	static void deleteAllTextures();
private:
	static vector<Texture*> allTexture;
	string path;
	string nameOfTexture;
	GLuint textureId;
	glm::vec2 textureWarpOption;

	Texture(string path , glm::vec2 textureWarpOption);
};

#endif