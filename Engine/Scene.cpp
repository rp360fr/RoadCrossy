#include "Scene.h"

Scene::Scene(std::string name,sf::Vector2u size)
{
	this->size = size;
	this->name = name;
	Obstacles.resize(750, nullptr);
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
void Scene::RemoveParamObject(GameObject* obj)
{
	auto it = std::find(objects.begin(), objects.end(), obj);
	if (it != objects.end())
	{
		delete* it;
		objects.erase(it);
	}
}
void Scene::Render(sf::RenderWindow& window)
{
	window.clear();
	for (GameObject* object : objects)
	{
		object->Render(window);
	}
	for (auto object = ground.rbegin(); object != ground.rend(); ++object)
	{
		(*object)->Render(window);
	}

	GameObject* player = GetPlayer(); // ← sorti de la boucle, une seule fois

	for (auto object = Obstacles.rbegin(); object != Obstacles.rend(); ++object)
	{
		if ((*object) == nullptr) continue;

		// Pas de joueur sur cette scène → rendu normal
		if (player == nullptr)
		{
			(*object)->Render(window);
			continue;
		}

		GameObject* bato = player->getBato();

		// Le joueur est sur un bateau : on skip le joueur ici,
		// il sera rendu après le bateau
		if (*object == player && bato != nullptr)
			continue;

		// Le bateau : on le rend, puis le joueur par-dessus
		if (bato != nullptr && *object == bato)
		{
			bato->Render(window);
			player->Render(window);
			continue;
		}

		(*object)->Render(window);
	}
	window.display();
}


void Scene::Destroy()
{

	for (GameObject* obj : ground)  if(obj)  delete obj;
	for (GameObject* obj : Obstacles) if (obj) delete obj;

	objects.clear();
	ground.clear();
	std::fill(Obstacles.begin(), Obstacles.end(), nullptr);

	if (LvLData) { delete LvLData; LvLData = nullptr; }
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
	for (auto& slot : Obstacles)
	{
		if (slot && slot->IsMarkedForDestruction())
		{
			GameObject* player = GetPlayer();
			if (player && player->getBato() == slot)
				player->setBato(nullptr);

			delete slot;
			slot = nullptr;
		}
	}
}