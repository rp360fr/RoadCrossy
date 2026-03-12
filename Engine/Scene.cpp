#include "Scene.h"

Scene::Scene(std::string name,sf::Vector2u size)
{
	this->size = size;
	this->name = name;
	Obstacles.resize(1500, nullptr);
}


void Scene::AddGroundObject(GameObject* obj)
{
	obj->setOwner(this);
	ground.push_back(obj);
}

void Scene::AddGameObject(GameObject* obj, std::pair<int,int> pos)
{

	obj->setOwner(this);
	Obstacles[pos.first+pos.second*15] = obj;
	
}

void Scene::AddMovingGameObject(GameObject* obj)
{

	obj->setOwner(this);
	MovingObstacles.push_back(obj);

}

void Scene::AddParamObject(GameObject* obj)
{
	obj->setOwner(this);
	objects.push_back(obj);
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
	for (GameObject* object : MovingObstacles)
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
	for (GameObject* object : MovingObstacles)
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

	// 4. Nettoyer les objets inactifs (APRÈS toutes les itérations)
	objects.erase(
		std::remove_if(objects.begin(), objects.end(),
			[](GameObject* obj) {
				if (!obj->getActive()) {
					std::cout << "[DEBUG] Suppression objet inactif" << std::endl;
					delete obj;
					return true;
				}
				return false;
			}),
		objects.end()
	);
}

void Scene::Render(sf::RenderWindow& window)
{
	for (GameObject* object : objects)
	{
		object->Render(window);
	}
	for (GameObject* object : ground)
	{
		object->Render(window);
	}
	for (auto object = Obstacles.rbegin(); object != Obstacles.rend(); ++object)
	{
		if((*object) != nullptr)
			(*object)->Render(window);
	}
	for (GameObject* object : MovingObstacles)
	{
		if(object)
			object->Render(window);
	}
	window.display();
}


void Scene::Destroy()
{
	for (GameObject* object : objects)
	{
		object->Destroy();
	}
}

void Scene::CleanupDestroyedObjects() {
	// Utiliser "objects" au lieu de "gameObjects" !
	for (auto it = objects.begin(); it != objects.end(); ) {
		if ((*it)->IsMarkedForDestruction()) {
			std::cout << "[DEBUG] Objet detruit a la position: ("
				<< (*it)->getTransform().pos.x << ", "
				<< (*it)->getTransform().pos.y << ")" << "Objet Type : " << (*it)->GetComponent<SpriteRenderer>()->getTexture() << std::endl;
			delete* it;
			it = objects.erase(it);
		}
		else {
			++it;
		}
	}
}