#include "Scene.h"

Scene::Scene(std::string name,sf::Vector2u size)
{
	this->size = size;
	this->name = name;
	Obstacles.resize(1500, nullptr);
}


void Scene::AddGroundObject(GameObject* obj)
{
	if (obj)
	{
		obj->setOwner(this);
		ground.push_back(obj);
	}
}

void Scene::AddGameObject(GameObject* obj, std::pair<int,int> pos)
{
	if (obj)
	{
		obj->setOwner(this);
		Obstacles[pos.first + pos.second * 15] = obj;
	}
}

void Scene::AddParamObject(GameObject* obj)
{
	if (obj)
	{
		obj->setOwner(this);
		objects.push_back(obj);
	}
}



void Scene::RemoveGameObject(GameObject* obj)
{
	auto object = std::find(objects.begin(), objects.end(), obj);
	if (object != objects.end())
	{
		delete* object;
		objects.erase(object);
	}
}


GameObject* Scene::getThisObjByText(std::string name)
{
	for (GameObject* object : objects)
	{
		if (object->GetComponent<Text>() != nullptr)
			if (object->GetComponent<Text>()->getText() == name)
				return object;
	}
}



void Scene::Start()
{
	for (GameObject* object : objects)
	{
		object->Start();
	}
	for (GameObject* object : ground)
	{
		object->Start();
	}
	for (GameObject* object : Obstacles)
	{
		if (object)
			object->Start();
	}
	if (LvLData != nullptr)
	{
		LvLData->Start();
		if (LvLData->GetComponent<AudioManager>() != nullptr)
			LvLData->GetComponent<AudioManager>()->Play();
	}
	clock.start();
}

void Scene::Update(sf::RenderWindow& window)
{
	// 1. Update tous les objets (sans supprimer pendant l'itération)
	for (GameObject* object : objects)
	{
		if (object && object->getActive())
		{
			object->Update();
		}
	}
	for (GameObject* object : ground)
	{
		if (object && object->getActive())
		{
			object->Update();
		}
	}
	for (GameObject* object : Obstacles)
	{
		if (object && object->getActive())
		{
			object->Update();
		}
	}

	// 2. Render
	Render(window);

	// 3. Nettoyer les objets marqués pour destruction
	CleanupDestroyedObjects();

}

void Scene::Render(sf::RenderWindow& window)
{
	for (GameObject* object : objects)
	{
		object->Render(window);
	}
	for (auto object = ground.rbegin(); object != ground.rend(); ++object)
	{
		(*object)->Render(window);
	}
	for (auto object = Obstacles.rbegin(); object != Obstacles.rend(); ++object)
	{
		if ((*object) != nullptr)
		{
			GameObject* player = GetPlayer();

			if (*object == player && player->getBato() != nullptr)
			{
				continue;
			}

			GameObject* bato = player->getBato();
			if (*object == bato)
			{
				bato->Render(window);

				player->Render(window);

				continue;
			}
			(*object)->Render(window);
		}
	}
	window.display();
}


void Scene::Destroy()
{
	for (GameObject* object : objects)
	{
		delete object;
		std::cout << "delete";
	}
	for (GameObject* object : ground)
	{
		delete object;
		std::cout << "delete";
	}
	for (GameObject* object : Obstacles)
	{
		delete object;
		std::cout << "delete";
	}
}

void Scene::CleanupDestroyedObjects() {
	for (auto it = objects.begin(); it != objects.end(); ) {
		if ((*it)->IsMarkedForDestruction()) 
		{
			std::cout << "delete";
			delete* it;
			it = objects.erase(it);
		}
		else {
			++it;
		}
	}
	for (GameObject* obj : Obstacles)
	{
		if (obj)
			if(obj->IsMarkedForDestruction())
			{
				std::cout << "delete";
				Obstacles[obj->getTransform().placement] = nullptr;
				delete obj;
			}
	}
}