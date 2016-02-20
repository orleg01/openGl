#include "Material.h"

std::vector<Material*> Material::allMaterials;
std::vector<Texture*> allTextureOfMaterial[aiTextureType_UNKNOWN + 1];

Material::Material(aiMaterial * material)
{
	basicColor = vec3(-1, -1, -1);
	this->myAiMaterial = material;
	material->Get(AI_MATKEY_NAME, this->name);
	
	aiColor3D colVec;
	GET_COLOR_VEC(AI_MATKEY_COLOR_DIFFUSE, this->myAiMaterial, diffuseColor);
	GET_COLOR_VEC(AI_MATKEY_COLOR_SPECULAR, this->myAiMaterial, specularColor);
	GET_COLOR_VEC(AI_MATKEY_COLOR_AMBIENT, this->myAiMaterial, ambientColor);
	GET_COLOR_VEC(AI_MATKEY_COLOR_EMISSIVE, this->myAiMaterial, emissiveColor);
	GET_COLOR_VEC(AI_MATKEY_COLOR_TRANSPARENT, this->myAiMaterial, transperentColor);
	
	int makro;
	GET_BOOL_PARAM(AI_MATKEY_ENABLE_WIREFRAME, this->myAiMaterial, wireFrame);
	GET_BOOL_PARAM(AI_MATKEY_TWOSIDED, this->myAiMaterial, twoSide);

	material->Get(AI_MATKEY_OPACITY, opacity);
	material->Get(AI_MATKEY_SHININESS, shininess);
	material->Get(AI_MATKEY_SHININESS_STRENGTH, shininess_strength);
	material->Get(AI_MATKEY_REFRACTI, refracti);
	
	int sizeOfArray = aiTextureType_UNKNOWN + 1;
	unsigned int numberOfMaps[aiTextureType_UNKNOWN + 1];
	for (unsigned int i = 0; i < sizeOfArray; i++)
	{
		numberOfMaps[i] = material->GetTextureCount((aiTextureType)i);
	}

	std::vector<aiString> allPath[aiTextureType_UNKNOWN + 1];
	for (int i = 0; i < sizeOfArray; i++)
	{
		for (int j = 0; j < numberOfMaps[i]; j++)
		{
			aiString aiStringTemp;
			material->GetTexture((aiTextureType)i, j, &aiStringTemp);
			allPath[i].push_back(aiStringTemp);
		}
	}

	for (int i = 0; i < sizeOfArray; i++)
	{
		for (int j = 0; j < numberOfMaps[i]; j++)
		{
			float tempy;
			material->Get(AI_MATKEY_TEXBLEND((aiTextureType)i, j), tempy);
			stengthOfTexture[i].push_back(tempy);
		}
	}
	SET_VECTOR_OF_ARRAY_IN_INFORMATION(AI_MATKEY_TEXOP , whichOperationPreform);
	SET_VECTOR_OF_ARRAY_IN_INFORMATION(AI_MATKEY_MAPPING , mapping);
	SET_VECTOR_OF_ARRAY_IN_INFORMATION(AI_MATKEY_UVWSRC, uvwsrc);
	SET_VECTOR_OF_ARRAY_IN_INFORMATION(AI_MATKEY_MAPPINGMODE_U, mappingMode_U);
	SET_VECTOR_OF_ARRAY_IN_INFORMATION(AI_MATKEY_MAPPINGMODE_V , mappingMode_V);
	SET_VECTOR_OF_ARRAY_IN_INFORMATION(AI_MATKEY_TEXFLAGS, texFlag);

	for (int i = 0; i < sizeOfArray; i++)
	{
		int sizeOfNextIteration = allPath[i].size();
		for (int j = 0; j < sizeOfNextIteration; j++)
		{
			allTextureOfMaterial[i].push_back(Texture::getTexture(string( allPath[i][j].C_Str()) , vec2(mappingMode_U[i][j] , mappingMode_V[i][j])));
		}
	}

}

Material::Material()
{
	this->basicColor = vec3(1, 0, 1);
}

Material* Material::getMaterial(aiMaterial* material)
{
	aiString str;
	material->Get(AI_MATKEY_NAME, str);
	for (Material* mat : allMaterials)
	{
		if (strcmp(mat->name.C_Str(), str.C_Str()) == 0)
			return mat;
	}
	return new Material(material);
}

Material* Material::getMaterial()
{
	for (Material* mat : allMaterials)
	{
		if (mat->basicColor == vec3(1, 0, 1))
			return mat;
	}
	Material* mat = new Material();
	allMaterials.push_back(mat);
	return mat;
}

void Material::bindThisMatirialToShader(GLuint shadId)
{
	Texture::setTexturesToShader(allTextureOfMaterial, shadId);
	if (basicColor != vec3(-1, -1, -1))
	{
		glUniform3f(glGetUniformLocation(shadId, "colorForObject"), basicColor.x , basicColor.y , basicColor.z);
	}
	else 
	{
		
	}
}

void Material::deleteAllMaterial()
{
	for (int i = 0; i < allMaterials.size(); i++)
		delete allMaterials[i];
}

void Material::deleteMaterial()
{
	for (int i = 0; i < aiTextureType_UNKNOWN + 1; i++)
		for (int j = 0; j < allTextureOfMaterial[i].size(); j++)
			delete allTextureOfMaterial[i][j];
}

