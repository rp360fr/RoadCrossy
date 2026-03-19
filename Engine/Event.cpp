#include "Event.h"


std::map<int, int> Event::lstId;
std::map<int, event> Event::lstEvent;

void Event::CreateEvent(int id, event evt) //Creer un event pour le jeu 
{
	if (id < 0)
		lstId[id] = 1;
	else
		lstId[id] = 0;
	lstEvent[id] = evt;

}

void Event::ProcessEvent()
{
    // 1. Collecter les IDs à fire sans toucher à la map
    std::vector<int> toFire;
    for (auto& [id, test] : lstId)
    {
        if (test == 1)
            toFire.push_back(id);
    }

    // 2. Désactiver les one-shot AVANT d'appeler les callbacks
    for (int id : toFire)
    {
        if (id > 0)
            lstId[id] = -1;
    }

    // 3. Appeler les callbacks (qui peuvent modifier lstId librement)
    for (int id : toFire)
    {
        if (lstEvent.count(id))
            lstEvent[id]();
    }
}

void Event::SetEventTrue(int id) // met un event a true
{
	if (lstId[id] == 0)
		lstId[id] = 1;
}
void Event::SetEventFalse(int id) // met un event a true
{
	if (lstId[id] == -1)
		lstId[id] = 0;
}

void Event::ClearAllEvents()
{
	lstId.clear();
	lstEvent.clear();
	std::cout << "Tous les events ont ete nettoyes" << std::endl;
}
