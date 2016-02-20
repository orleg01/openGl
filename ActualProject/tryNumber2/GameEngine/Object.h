#ifndef __OBJECT__H
#define __OBJECT__H

#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Component.h"
#include "Screen.h"
#include "Shader.h"

class Object
{
public:
	Object(Mesh* mesh, bool wasAlocate = false);
	Object(bool wasAlocate = false);

	~Object();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	void addChild(Object* child);
	void Draw(mat4 viewMatrix);
	void SetMesh(Mesh* mesh);
	void SetMaterial(Material* material);
	void Update(double deltaTime);
	void LoadFromFile(string path, bool toMargeAll, bool toSplitMesh);
	Transform& GetTransform();
	void buildShader();

private:
	void Object::SetNullMaterial();
	Transform transform;
	Mesh* mesh = nullptr;
	Material* material = nullptr;
	vector<Object*> children;
	Object* parent = nullptr;
	Shader* shad;

	vector<Component*> components;

	bool alocateMaterial = false;

	bool wasAlocate = false;
};

#endif