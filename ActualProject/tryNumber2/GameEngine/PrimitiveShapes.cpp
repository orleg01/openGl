#include "Mesh.h"

Mesh::Mesh(ShapesTypes type, int resX, int resY, bool wasAlocate) :Mesh(wasAlocate)
{
	vector<GLfloat> vertices;
	vector<GLuint> indices;
	const double PI = 3.14159265359;
	switch (type)
	{
	case CUBE:
	{
		useNormals = true;
		useUVs = true;
		useTangens = true;
		useColors = true;
		useIndices = false;

		vertices = {
			-0.5f, -0.5f, -0.5f,  0, 0, -1,	0.0f, 0.0f, -1, 0, 0,  1, 0, 0, 1,
			 0.5f, -0.5f, -0.5f,  0, 0, -1,	1.0f, 0.0f, -1, 0, 0,  1, 0, 0, 1,
			 0.5f,  0.5f, -0.5f,  0, 0, -1,	1.0f, 1.0f, -1, 0, 0,  1, 0, 0, 1,
			 0.5f,  0.5f, -0.5f,  0, 0, -1,	1.0f, 1.0f, -1, 0, 0,  1, 0, 0, 1,
			-0.5f,  0.5f, -0.5f,  0, 0, -1,	0.0f, 1.0f, -1, 0, 0,  1, 0, 0, 1,
			-0.5f, -0.5f, -0.5f,  0, 0, -1,	0.0f, 0.0f, -1, 0, 0,  1, 0, 0, 1,

			-0.5f, -0.5f,  0.5f,  0, 0,  1,	0.0f, 0.0f, 1, 0, 0,  1, 1, 0, 1,
			 0.5f, -0.5f,  0.5f,  0, 0,  1,	1.0f, 0.0f, 1, 0, 0,  1, 1, 0, 1,
			 0.5f,  0.5f,  0.5f,  0, 0,  1,	1.0f, 1.0f, 1, 0, 0,  1, 1, 0, 1,
			 0.5f,  0.5f,  0.5f,  0, 0,  1,	1.0f, 1.0f, 1, 0, 0,  1, 1, 0, 1,
			-0.5f,  0.5f,  0.5f,  0, 0,  1,	0.0f, 1.0f, 1, 0, 0,  1, 1, 0, 1,
			-0.5f, -0.5f,  0.5f,  0, 0,  1,	0.0f, 0.0f, 1, 0, 0,  1, 1, 0, 1,

			-0.5f,  0.5f,  0.5f, -1, 0, 0,	1.0f, 0.0f,  0,-1, 0,  0, 1, 1, 1,
			-0.5f,  0.5f, -0.5f, -1, 0, 0,	1.0f, 1.0f,  0,-1, 0,  0, 1, 1, 1,
			-0.5f, -0.5f, -0.5f, -1, 0, 0,	0.0f, 1.0f,  0,-1, 0,  0, 1, 1, 1,
			-0.5f, -0.5f, -0.5f, -1, 0, 0,	0.0f, 1.0f,  0,-1, 0,  0, 1, 1, 1,
			-0.5f, -0.5f,  0.5f, -1, 0, 0,	0.0f, 0.0f,  0,-1, 0,  0, 1, 1, 1,
			-0.5f,  0.5f,  0.5f, -1, 0, 0,	1.0f, 0.0f,  0,-1, 0,  0, 1, 1, 1,

			 0.5f,  0.5f,  0.5f,  1, 0, 0,	1.0f, 0.0f,  0, 1, 0,  1, 0, 1, 1,
			 0.5f,  0.5f, -0.5f,  1, 0, 0,	1.0f, 1.0f,  0, 1, 0,  1, 0, 1, 1,
			 0.5f, -0.5f, -0.5f,  1, 0, 0,	0.0f, 1.0f,  0, 1, 0,  1, 0, 1, 1,
			 0.5f, -0.5f, -0.5f,  1, 0, 0,	0.0f, 1.0f,  0, 1, 0,  1, 0, 1, 1,
			 0.5f, -0.5f,  0.5f,  1, 0, 0,	0.0f, 0.0f,  0, 1, 0,  1, 0, 1, 1,
			 0.5f,  0.5f,  0.5f,  1, 0, 0,	1.0f, 0.0f,  0, 1, 0,  1, 0, 1, 1,

			-0.5f, -0.5f, -0.5f,  0,-1, 0,	0.0f, 1.0f,  0, 0,-1,  0, 0, 1, 1,
			 0.5f, -0.5f, -0.5f,  0,-1, 0,	1.0f, 1.0f,  0, 0,-1,  0, 0, 1, 1,
			 0.5f, -0.5f,  0.5f,  0,-1, 0,	1.0f, 0.0f,  0, 0,-1,  0, 0, 1, 1,
			 0.5f, -0.5f,  0.5f,  0,-1, 0,	1.0f, 0.0f,  0, 0,-1,  0, 0, 1, 1,
			-0.5f, -0.5f,  0.5f,  0,-1, 0,	0.0f, 0.0f,  0, 0,-1,  0, 0, 1, 1,
			-0.5f, -0.5f, -0.5f,  0,-1, 0,	0.0f, 1.0f,  0, 0,-1,  0, 0, 1, 1,

			-0.5f,  0.5f, -0.5f,  0, 1, 0,	0.0f, 1.0f,  0, 0, 1,  0, 1, 0, 1,
			 0.5f,  0.5f, -0.5f,  0, 1, 0,	1.0f, 1.0f,  0, 0, 1,  0, 1, 0, 1,
			 0.5f,  0.5f,  0.5f,  0, 1, 0,	1.0f, 0.0f,	 0, 0, 1,  0, 1, 0, 1,
			 0.5f,  0.5f,  0.5f,  0, 1, 0,	1.0f, 0.0f,	 0, 0, 1,  0, 1, 0, 1,
			-0.5f,  0.5f,  0.5f,  0, 1, 0,	0.0f, 0.0f,  0, 0, 1,  0, 1, 0, 1,
			-0.5f,  0.5f, -0.5f,  0, 1, 0,	0.0f, 1.0f,  0, 0, 1,  0, 1, 0, 1
		};
	}
	break;
	case SPHERE:
		useNormals = true;
		useUVs = true;
		useTangens = true;
		useColors = true;
		useIndices = true;
		
		for (int angleHeight = 0; angleHeight < resY; angleHeight++)
		{
			double angle = (angleHeight / (double)(resY - 1)) * PI;
			GLfloat height = cos(angle) * 0.5;
			double radius = sin(angle) * 0.5;
			for (int angleSlic = 0; angleSlic < resX; angleSlic++)
			{
				angle = (angleSlic / (double)resX) * PI * 2;
				GLfloat x = cos(angle) * radius;
				GLfloat z = sin(angle) * radius;

				//position
				vertices.push_back(x);
				vertices.push_back(height);
				vertices.push_back(z);

				//normal
				vec3 normal(x * 2, height * 2, z * 2);
				vertices.push_back(normal.x);
				vertices.push_back(normal.y);
				vertices.push_back(normal.z);
				

				//uvs
				GLfloat u = angleHeight / (float)(resY - 1);
				GLfloat v = angleSlic / (float)(resX - 1);
				vertices.push_back(u);
				vertices.push_back(v);

				//tangen
				vec3 tangen = cross(normal, vec3(0, 1, 0));
				vertices.push_back(tangen.x);
				vertices.push_back(tangen.y);
				vertices.push_back(tangen.z);

				//color
				vec3 color = vec3(0.5) + normal * 0.5f;
				vertices.push_back(color.x);
				vertices.push_back(color.y);
				vertices.push_back(color.z);
				vertices.push_back(1);
			}
		}

		for (int i = 0; i < resX * (resY - 1); i++)
		{
			int nextIndex = i - (i % resX) + (i + 1) % resX;
			
			indices.push_back(i);
			indices.push_back(nextIndex);
			indices.push_back(i + resX);

			indices.push_back(nextIndex);
			indices.push_back(nextIndex + resX);
			indices.push_back(i + resX);
		}
		
		break;
	case PLANE:
	{
		useNormals = true;
		useUVs = true;
		useTangens = true;
		useColors = true;
		useIndices = true;
		vertices = {
			-1.0, -1.0, 0  , 0, 0, 1.0  , 0 , 0,  1, 0, 0,  1, 0, 0, 1,
			 1.0, -1.0, 0  , 0, 0, 1.0  , 1 , 0,  1, 0, 0,  0, 1, 0, 1,
			 1.0,  1.0, 0  , 0, 0, 1.0  , 1 , 1,  1, 0, 0,  0, 0, 1, 1,
			-1.0,  1.0, 0  , 0, 0, 1.0  , 0 , 1,  1, 0, 0,  1, 1, 1, 1
		};

		indices = {
			0, 1, 2,
			2, 3, 0,
		};
	}
	break;
	case CYLINDER:
		useNormals = true;
		useUVs = true;
		useTangens = true;
		useColors = true;
		useIndices = true;

		for (int angleHeight = 0; angleHeight < resY; angleHeight++)
		{
			GLfloat height = angleHeight / (double)(resY - 1) - 0.5;
			double radius = 0.5;
			for (int angleSlic = 0; angleSlic < resX; angleSlic++)
			{
				double angle = (angleSlic / (double)resX) * PI * 2;
				GLfloat x = cos(angle) * radius;
				GLfloat z = sin(angle) * radius;

				//position
				vertices.push_back(x);
				vertices.push_back(height);
				vertices.push_back(z);

				//normal
				vertices.push_back(x);
				vertices.push_back(height);
				vertices.push_back(z);
				vec3 normal(x, height, z);

				//uvs
				GLfloat u = angleHeight / (float)(resY - 1);
				GLfloat v = angleSlic / (float)(resX - 1);
				vertices.push_back(u);
				vertices.push_back(v);

				//tangen
				vec3 tangen = cross(normal, vec3(0, 1, 0));
				vertices.push_back(tangen.x);
				vertices.push_back(tangen.y);
				vertices.push_back(tangen.z);

				//color
				vec3 color = vec3(0.5) + normal * 0.5f;
				vertices.push_back(color.x);
				vertices.push_back(color.y);
				vertices.push_back(color.z);
				vertices.push_back(1);
			}
		}
		//vertex button
		//position
		vertices.push_back(0);
		vertices.push_back(-0.5);
		vertices.push_back(0);

		//normal
		vertices.push_back(0);
		vertices.push_back(-1);
		vertices.push_back(0);

		//uvs
		vertices.push_back(0);
		vertices.push_back(0.5);

		//tangen
		vertices.push_back(1);
		vertices.push_back(0);
		vertices.push_back(0);

		//color
		vertices.push_back(1);
		vertices.push_back(0);
		vertices.push_back(0);
		vertices.push_back(1);

		//vertex top
		//position
		vertices.push_back(0);
		vertices.push_back(0.5);
		vertices.push_back(0);

		//normal
		vertices.push_back(0);
		vertices.push_back(1);
		vertices.push_back(0);

		//uvs
		vertices.push_back(1);
		vertices.push_back(0.5);

		//tangen
		vertices.push_back(-1);
		vertices.push_back(0);
		vertices.push_back(0);

		//color
		vertices.push_back(0);
		vertices.push_back(0);
		vertices.push_back(1);
		vertices.push_back(1);
		for (int i = 0; i < resX * (resY - 1); i++)
		{
			int nextIndex = i - (i % resX) + (i + 1) % resX;

			indices.push_back(i);
			indices.push_back(nextIndex);
			indices.push_back(i + resX);

			indices.push_back(nextIndex);
			indices.push_back(nextIndex + resX);
			indices.push_back(i + resX);
		}
		for (int i = 0; i < resX + 1; i++)
		{
			indices.push_back(i);
			indices.push_back((i + 1) % resX);
			indices.push_back(resX * resY);
		}
		int offset = resX * (resY - 1);
		for (int i = 0; i < resX + 1; i++)
		{
			indices.push_back(offset + i);
			indices.push_back(offset + (i + 1) % resX);
			indices.push_back(resX * resY + 1);
		}
		break;
	}
	numOfUVChannels = 1;
	numOfColorChannels = 1;
	SetMesh(vertices, &indices, (3 + 3 + 2 + 3 + 4));
}