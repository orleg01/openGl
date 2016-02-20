#include "ModelImporter.h"

void createChildren(aiNode * mRootNode, const aiScene * scene, Object* parent);

void Object::LoadFromFile(string path , bool toMargeAll , bool toSplitMesh)
{
	Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | 
		aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals | 
		(toMargeAll? aiProcess_OptimizeMeshes:0) |
		(toSplitMesh? aiProcess_SplitLargeMeshes:0));

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}
	string directory = path.substr(0, path.find_last_of('/'));

	unsigned int index = scene->mRootNode->mMeshes[0];
	mesh = new Mesh(scene->mMeshes[index]);

	createChildren(scene->mRootNode, scene , this);
}

void createChildren(aiNode * mRootNode, const aiScene * scene , Object* parent)
{
	for (GLuint i = 0; i < mRootNode->mNumChildren; i++)
	{
		Object* child = new Object(true);
		parent->addChild(child);
		aiNode* node = mRootNode->mChildren[i];
		if (node->mNumMeshes != 0)
		{
			aiMesh* aiMesh = scene->mMeshes[node->mMeshes[0]];
			Mesh* mesh = new Mesh(aiMesh, true);
			unsigned int matIndex = aiMesh->mMaterialIndex;
			aiMaterial* material = scene->mMaterials[matIndex];

			material->mProperties[1]->mSemantic;
		}
		createChildren(node, scene, child);
	}
}