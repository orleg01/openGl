
#ifndef __MATERIAL_H
#define __MATERIAL_H

//normal include
#include <soil\SOIL.h>
#include <iostream>
#include <assimps\assimp\material.h>
#include <vector>
#include <glm\glm.hpp>

//my Includes

class Shader;
struct ShaderParam;
class Mesh;

#include "Texture.h"

using namespace Assimp;
using namespace glm;

#define GET_COLOR_VEC(TYPE ,myAiMaterial , temp) \
											myAiMaterial->Get(TYPE , colVec); \
											temp = vec3(colVec.r , colVec.g , colVec.b);

#define GET_BOOL_PARAM(TYPE , myAiMaterial , temp)	 \
													 myAiMaterial->Get(TYPE , makro); \
													 temp = makro != 0;

#define SET_VECTOR_OF_ARRAY_IN_INFORMATION(TYPE , VECTOR) \
															for (int i = 0; i < sizeOfArray; i++)\
															{\
																for (int j = 0; j < numberOfMaps[i]; j++)\
																{\
																	int tempy;\
																	material->Get(TYPE((aiTextureType)i, j), tempy);\
																	VECTOR[i].push_back(tempy);\
																}\
															}


class Material
{
public:
	static Material* getMaterial(aiMaterial* material);
	static Material* getMaterial();
	void bindThisMatirialToShader(GLuint shadId);
	static void deleteAllMaterial();
	void deleteMaterial();


	//friends :)
	friend Shader* GetShader(Material* mat, Mesh* mesh);
	friend ShaderParam InitializeStruct(Material* mat, Mesh* mesh);


private:

	static std::vector<Material*> allMaterials;
	//basic Color
	vec3 basicColor;

	//ai variable
	aiMaterial* myAiMaterial;
	aiString name;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	glm::vec3 ambientColor;
	glm::vec3 emissiveColor;
	glm::vec3 transperentColor;

	bool wireFrame;
	bool twoSide;

	//int howTheBlendWillWork;

	float opacity;
	float shininess;
	float shininess_strength;
	float refracti;

	Material(aiMaterial* material);

	std::vector<float> stengthOfTexture[aiTextureType_UNKNOWN + 1];
	std::vector<int> whichOperationPreform[aiTextureType_UNKNOWN + 1];
	std::vector<int> mapping[aiTextureType_UNKNOWN + 1];
	std::vector<int> uvwsrc[aiTextureType_UNKNOWN + 1];
	std::vector<int> mappingMode_U[aiTextureType_UNKNOWN + 1];
	std::vector<int> mappingMode_V[aiTextureType_UNKNOWN + 1];
	std::vector<int> texFlag[aiTextureType_UNKNOWN + 1];

	std::vector<Texture*> allTextureOfMaterial[aiTextureType_UNKNOWN + 1];

	Material();
};


#endif