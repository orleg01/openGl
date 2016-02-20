#include "Object.h"

Object::Object(Mesh* mesh , bool wasAlocate):Object(wasAlocate)
{
	this->mesh = mesh;
}

Object::Object(bool wasAlocate)
{
	this->wasAlocate = wasAlocate;
}

Object::~Object()
{
	for (Object* child : children)
	{
		if (child->wasAlocate)
			delete child;
	}
	if (mesh != nullptr && mesh->WasAlocate())
		delete mesh;
}

void Object::AddComponent(Component * component)
{
	components.push_back(component);
	SetObject(component, this);
}

void Object::RemoveComponent(Component * component)
{
	REMOVE_FROM_VECTOR_BY_ELEMENT(components, component);
}

void Object::addChild(Object * child)
{
	children.push_back(child);
	child->parent = this;
	child->GetTransform().SetParent(&transform);
}

void Object::SetNullMaterial() 
{
	if (material == nullptr)
	{
		alocateMaterial = true;
		material = Material::getMaterial();
	}
}

void Object::Draw(mat4 viewMatrix)
{
	
	for (Object* object : children)
	{
		object->Draw(viewMatrix);
	}

	if (material == nullptr)
	{
		alocateMaterial = true;
		material = Material::getMaterial();
	}
	
	shad->UseShader();
	material->bindThisMatirialToShader(this->shad->getShaderId());
	GLuint shaderProgram = this->shad->getShaderId();
	transform.bind(shaderProgram);
	GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	mesh->Draw();
}

void Object::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void Object::SetMaterial(Material * material)
{
	if (this->alocateMaterial)
	{
		delete this->material;
		this->alocateMaterial = false;
	}
	this->material = material;
}

void Object::Update(double deltaTime)
{
	for (Component* component : components)
		component->Update(deltaTime);
}

Transform & Object::GetTransform()
{
	return transform;
}

void Object::buildShader()
{
	if (material == nullptr)
		SetNullMaterial();
	shad = Shader::GetShader(material , mesh);
}
