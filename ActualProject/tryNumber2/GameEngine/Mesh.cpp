#include "Mesh.h"

#define SET_VERTEX_PROPERTY(SIZE_OF_PROPERTY , OFFSET , INDEX) {glEnableVertexAttribArray(INDEX);\
																glVertexAttribPointer(INDEX++, SIZE_OF_PROPERTY, GL_FLOAT, GL_FALSE, \
																				sizeof(GLfloat) * sizeOfVertex, (GLvoid*)(OFFSET * sizeof(GLfloat)));\
																OFFSET += SIZE_OF_PROPERTY;}

#define CHECK_COMPONENT(CHECKED_COMPONENT) {if(component == CHECKED_COMPONENT)return location;}

void Mesh::SetMesh(vector<GLfloat>& vertices , vector<GLuint>* indices , int sizeOfVertex)
{
	glGenVertexArrays(1, &VAO);

	size = vertices.size()/sizeOfVertex;

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	if (useIndices)
	{
		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		size = indices->size();
	}

	int index = 0;
	int offSet = 0;
	// Vertex Positions
	SET_VERTEX_PROPERTY(3 , offSet , index);
	// Vertex Normals
	if (useNormals)
		SET_VERTEX_PROPERTY(3, offSet, index);
	
	// Vertex Texture Coords
	if (useUVs)
		SET_VERTEX_PROPERTY(2 * numOfUVChannels, offSet, index);
	
	// Vertex Tangen
	if (useTangens)
		SET_VERTEX_PROPERTY(3, offSet, index);
	
	// Vertex Color
	if (useColors)
		SET_VERTEX_PROPERTY(4 * numOfColorChannels, offSet, index);

	glBindVertexArray(0);
}



Mesh::Mesh(bool wasAlocate)
{
	this->wasAlocate = wasAlocate;
}

Mesh::Mesh(vector<vec3>* postions, vector<vec2>* uvs, vector<vec3>* normals, vector<vec3>* tangens, vector<GLuint>* indices, vector<vec4>* colors, bool wasAlocate):Mesh(wasAlocate)
{
	if (postions == nullptr)
	{
		throw "THE POSITION VERCTOR CAN'T BE NULL";
	}
	vector<GLfloat> vertices;

	int sizeOfVertex = 3;
	if (useUVs = uvs != nullptr)
	{
		sizeOfVertex += 2;
	}
	if (useNormals = normals != nullptr)
	{
		sizeOfVertex += 3;
	}
	if (useTangens = tangens != nullptr)
	{
		sizeOfVertex += 3;
	}
	if (useColors = colors != nullptr)
	{
		sizeOfVertex += 4;
	}
	useIndices = indices != nullptr;

	for (int i = 0; i < postions->size(); i++)
	{
		vertices.push_back((*postions)[i].x);
		vertices.push_back((*postions)[i].y);
		vertices.push_back((*postions)[i].z);

		if (useNormals)
		{
			vertices.push_back((*normals)[i].x);
			vertices.push_back((*normals)[i].y);
			vertices.push_back((*normals)[i].z);
		}

		if (useUVs)
		{
			vertices.push_back((*uvs)[i].x);
			vertices.push_back((*uvs)[i].y);
		}
		if (useTangens)
		{
			vertices.push_back((*tangens)[i].x);
			vertices.push_back((*tangens)[i].y);
			vertices.push_back((*tangens)[i].z);
		}
		if (useColors)
		{
			vertices.push_back((*colors)[i].x);
			vertices.push_back((*colors)[i].y);
			vertices.push_back((*colors)[i].z);
			vertices.push_back((*colors)[i].w);
		}
	}
	SetMesh(vertices, indices, sizeOfVertex);
}

Mesh::Mesh(aiMesh * mesh, bool wasAlocate) :Mesh(wasAlocate)
{
	vector<GLfloat> vertices;
	int sizeOfVertex = 3;
	if (useUVs = mesh->HasTextureCoords(0))
	{
		numOfUVChannels = mesh->GetNumUVChannels();
		sizeOfVertex += 2 * numOfUVChannels;
	}
	if (useNormals = mesh->HasNormals())
	{
		sizeOfVertex += 3;
	}
	if (useTangens = mesh->HasTangentsAndBitangents())
	{
		sizeOfVertex += 3;
	}
	if (useColors = mesh->HasVertexColors(0))
	{
		numOfColorChannels = mesh->GetNumColorChannels();
		sizeOfVertex += 4 * numOfColorChannels;
	}
	useIndices = mesh->HasFaces();
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		if (useNormals)
		{
			vertices.push_back(mesh->mNormals[i].x);
			vertices.push_back(mesh->mNormals[i].y);
			vertices.push_back(mesh->mNormals[i].z);
		}

		if (useUVs)
		{
			for (int j = 0; j < numOfUVChannels; j++)
			{
				vertices.push_back(mesh->mTextureCoords[j][i].x);
				vertices.push_back(mesh->mTextureCoords[j][i].y);
			}
		}
		if (useTangens)
		{
			vertices.push_back(mesh->mTangents[i].x);
			vertices.push_back(mesh->mTangents[i].y);
			vertices.push_back(mesh->mTangents[i].z);
		}
		if (useColors)
		{
			for (int j = 0; j < numOfColorChannels; j++)
			{
				vertices.push_back(mesh->mColors[j][i].r);
				vertices.push_back(mesh->mColors[j][i].g);
				vertices.push_back(mesh->mColors[j][i].b);
				vertices.push_back(mesh->mColors[j][i].a);
			}
		}
	}
	if (useIndices)
	{
		vector<GLuint> indices;

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace* face = mesh->mFaces + i;
			for (int indexNum = 0; indexNum < face->mNumIndices;indexNum++)
			{
				indices.push_back(face->mIndices[indexNum]);
			}
		}

		SetMesh(vertices, &indices, sizeOfVertex);	
	}
	
	SetMesh(vertices, nullptr, sizeOfVertex);
	
}

bool Mesh::WasAlocate()
{
	return wasAlocate;
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	if(useIndices)
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, size);
	glBindVertexArray(0);
}

bool Mesh::UseUVs()
{
	return useUVs;
}

bool Mesh::UseNormals()
{
	return useNormals;
}

bool Mesh::UseTangens()
{
	return useTangens;
}

bool Mesh::UseIndices()
{
	return useIndices;
}

bool Mesh::UseColors()
{
	return useColors;
}

int Mesh::GetNumOfUVChannels()
{
	return numOfUVChannels;
}

int Mesh::GetNumOfColorChannels()
{
	return numOfColorChannels;
}

int Mesh::GetComponentLocation(MeshVertexComponents component)
{
	int location = 0;
	CHECK_COMPONENT(POSITION)
	if (useNormals)
		location++;
	CHECK_COMPONENT(NORMAL);
	if (useUVs)
		location++;
	CHECK_COMPONENT(UV);
	if (useTangens)
		location++;
	CHECK_COMPONENT(TANGEN);
	if (useColors)
		location++;
	CHECK_COMPONENT(COLOR);
	return -1;
}

vector<MeshVertexComponents> Mesh::GetOrderOfVertexInMesh()
{
	vector<MeshVertexComponents> order;
	order.push_back(POSITION);
	if (useNormals)
		order.push_back(NORMAL);
	if (useUVs)
		order.push_back(UV);
	if (useTangens)
		order.push_back(TANGEN);
	if (useColors)
		order.push_back(COLOR);
	return order;
}

