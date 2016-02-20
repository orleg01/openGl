#ifndef __SHADER_H
#define __SHADER_H

// normal imports

#include <glew\GL\glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
//my imports

class Shader;
#include "DefinerForShader.h"
#include "Material.h"
#include "Mesh.h"

using namespace std;
using namespace glm;


#define ENTER_NUMBER_OF_ITEMS_IN_VECTOR(myArray , arrayOfVector ) \
for(int i = 0 ; i < aiTextureType_UNKNOWN + 1 ; i++)\
{ \
	myArray[i] = arrayOfVector[i].size();\
}

#define EQUALS_BETWEEN_ARRAYS(arr1 , arr2) \
{\
	for(int i = 0 ; i < aiTextureType_UNKNOWN + 1 ; i++) \
	{\
		if(arr1[i] != arr2[i]) \
			return false;\
	}\
}

enum VertexShaderVersion 
{
	BASIC_VS_VER ,
	NUMBER_OF_VERTEX_SHADER_VERSION
};

enum FragmentShaderVersion
{
	BASIC_FS_VER ,
	NUMBER_OF_FRAGMENR_SHADER_VERSION
};

class ShaderParam
{
public:
	//material ..
	bool diffuseColor = false; 
	bool specularColor = false;
	bool ambientColor = false;
	bool emissiveColor = false;
	bool opacity = false;
	bool shininess = false;
	bool refracti = false;

	//number of texture and type
	
	int numberOfstengthOfTexture[aiTextureType_UNKNOWN + 1];
	int numberOfWhichOperationPreform[aiTextureType_UNKNOWN + 1];
	int numberOfMapping[aiTextureType_UNKNOWN + 1];
	int numberOfUvwsrc[aiTextureType_UNKNOWN + 1];
	int numberOfTexFlag[aiTextureType_UNKNOWN + 1];

	// mesh ..

	bool useUV;
	bool useNormals;
	bool useTangens;
	bool useColors;

	bool operator== (ShaderParam& shadPar) 
	{
		if(this->diffuseColor == shadPar.diffuseColor)
			if (this->specularColor == shadPar.specularColor)
				if (this->ambientColor == shadPar.ambientColor)
					if (this->emissiveColor == shadPar.emissiveColor)
						if (this->opacity == shadPar.opacity)
							if (this->shininess == shadPar.shininess)
								if (this->refracti == shadPar.refracti)
									if (this->useUV == shadPar.useUV)
										if (this->useNormals == shadPar.useNormals)
											if (this->useTangens == shadPar.useTangens)
												if (this->useColors == shadPar.useColors)
												{
													EQUALS_BETWEEN_ARRAYS(this->numberOfstengthOfTexture, shadPar.numberOfstengthOfTexture);
													EQUALS_BETWEEN_ARRAYS(this->numberOfWhichOperationPreform, shadPar.numberOfWhichOperationPreform);
													EQUALS_BETWEEN_ARRAYS(this->numberOfMapping, shadPar.numberOfMapping);
													EQUALS_BETWEEN_ARRAYS(this->numberOfUvwsrc, shadPar.numberOfUvwsrc);
													EQUALS_BETWEEN_ARRAYS(this->numberOfTexFlag, shadPar.numberOfTexFlag);
													return true;
												}
		return false;
	}
};



class Shader
{
public:

	static Shader* GetShader(Material* mat, Mesh* mesh);
	friend ShaderParam InitializeStruct(Material* mat, Mesh* mesh);

	GLuint getShaderId();
	VertexShaderVersion getVertexVersion(ShaderParam* shadParam);
	FragmentShaderVersion getFragmentVersion(ShaderParam* shadParam);

	void UseShader();

private:

	static vector<Shader*> allShader;
	GLuint shaderId;
	ShaderParam shadStructParam;


	Shader(Material* mat, Mesh* mes , ShaderParam shadeStruct);
	


};


#endif
