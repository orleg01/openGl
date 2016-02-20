#ifndef __MESH__H
#define __MESH__H

#include <vector>
#include <glm\glm.hpp>
#include <glew\GL\glew.h>
#include <assimps\assimp/scene.h>

using namespace glm;
using namespace std;

enum ShapesTypes
{
	CUBE , SPHERE , PLANE , CYLINDER
};

enum MeshVertexComponents
{
	POSITION , NORMAL , UV , TANGEN , COLOR
};

class Mesh
{
public:
	Mesh(vector<vec3>* postions, vector<vec2>* uvs , vector<vec3>* normals , vector<vec3>* tangens ,vector<GLuint>* indices, vector<vec4>* colors , bool wasAlocate = false);
	Mesh(ShapesTypes type, int resX = 10, int resY = 10, bool wasAlocate = false);
	Mesh(aiMesh* mesh , bool wasAlocate = false);
	
	bool WasAlocate();
	void Draw();

	bool UseUVs();
	bool UseNormals();
	bool UseTangens();
	bool UseIndices();
	bool UseColors();
	
	int GetNumOfUVChannels();
	int GetNumOfColorChannels();
	
	int GetComponentLocation(MeshVertexComponents component);
	vector<MeshVertexComponents> GetOrderOfVertexInMesh();

private:
	GLuint VAO;
	GLuint size;

	bool wasAlocate = false;

	bool useUVs;
	bool useNormals;
	bool useTangens;
	bool useIndices;
	bool useColors;

	int numOfUVChannels;
	int numOfColorChannels;

	void SetMesh(vector<GLfloat>& vertices, vector<GLuint>* indices, int sizeOfVertex);
	Mesh(bool wasAlocate = false);
	
	char* propertiesNames[5] = { "Position" , "Normal" , "Tangen" , "Color" };
};

#endif

