#pragma once
#include "Engine.h"
#include "Component.h"
#include "Transform.h"

class Component;



class GameObject
{
private:
	
	Scene* owner;
	std::string name;
	bool active;
	Transform transform;
	std::vector<Component*> components;
	bool markedForDestruction = false;
	bool clickable = false;
	GameObject* Bato = nullptr;

public:

	//Constructeurs
	GameObject(int x, int y);
	GameObject(sf::Vector2f position);

	//Get
	bool getClickable() { return clickable; }
	bool getActive() { return active; }
	Scene* getOwner() { return owner; }
	GameObject* getBato() { return Bato; }
	Transform& getTransform();
	template<typename T>
	T* GetComponent(size_t index = 0)
	{
		size_t count = 0;
		for (Component* component : components)
		{
			if (T* casted = dynamic_cast<T*>(component))
			{
				if (count == index)
					return casted;
				++count;
			}
		}
		return nullptr;
	}

	template<typename T>
	void RemoveComponent(size_t index = 0)
	{
		size_t count = 0;
		for (auto it = components.begin(); it != components.end(); ++it)
		{
			if (T* casted = dynamic_cast<T*>(*it))
			{
				if (count == index)
				{
					delete* it;
					components.erase(it);
					return;
				}
				++count;
			}
		}
	}

	//Set
	void setClickable(bool B) { clickable = B; }
	void setOwner(Scene* s);
	void SetPosition(sf::Vector2f pos);
	void setBato(GameObject* bato) { Bato = bato; }

	//Autres
	Component* AddComponent(Component* component);
	void Start();
	void Update();
	void Render(sf::RenderWindow& window);
	void Destroy();

	bool IsMarkedForDestruction() const {return markedForDestruction;}
	
	
};

