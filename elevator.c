#include <stdlib.h>
#include "elevator.h"
#include "person.h"

Elevator *create_elevator(int capacity, int currentFloor, PersonList* persons)
{
    Elevator* res = (Elevator*)malloc(sizeof(Elevator));
    res->capacity = capacity;
    res->currentFloor = currentFloor;
    res->persons = persons;
    return res;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList** waitingLists)
{
    Building* res = (Building*)malloc(sizeof(Building));
    res->nbFloor = nbFloor;
    res->elevator = elevator;
    res->waitingLists = waitingLists;
    return res;
}

// Renvoie la nouvelle liste des personnes dans l'ascenseur en faisant sortir ceux qui sont arrivés
PersonList* exitElevator(Elevator *e)
{
    // On va parcourir toutes les personnes dans l'ascenseur
    PersonList* current = e->persons;       // Pointeur de la personne que l'on est en train de regarder
    PersonList* previous = NULL;            // On garde un pointeur de la personne précédente pour réorganiser la liste
    while(current != NULL)
    {
        if(current->person->dest == e->currentFloor)
        {
            if(previous == NULL)
            {
                e->persons = e->persons->next;     // On pop la première personne de l'ascenseur
            }
            else
            {
                previous->next = current->next;     // Si on change le lien de la liste
            }
        }

        previous = current;
        current = current->next;
    }

    return e->persons;
    
}

// Rempli l'ascenseur et renvoie la nouvelle file d'attente
PersonList* enterElevator(Elevator *e, PersonList *waitingList)
{
    // Tant qu'il reste des gens dans la file d'attente et que l'ascenseur n'est pas plein
    while(length(e->persons) < e->capacity && length(waitingList) > 0) 
    {
        if(waitingList->person->dest != e->currentFloor)
        {
            e->persons = insert(waitingList->person, e->persons);       // On insère dans l'ascenseur
        }

        waitingList = waitingList->next;                                // On pop de la file

    }

    return waitingList;
}

void stepElevator(Building *b)
{
    if(b->elevator->currentFloor == b->elevator->targetFloor)
    {
        // Si on est au bon étage
        int currentFloor = b->elevator->currentFloor;
        b->elevator->persons = exitElevator(b->elevator);   // On fait sortir les bonnes personnes de l'ascenseur
        b->waitingLists[currentFloor] = enterElevator(b->elevator, b->waitingLists[currentFloor]);  // On fait rentrer les autres si ils le peuvent
    }
    else
    {
        // On fait bouger l'ascenseur dans la bonne direction (+1 ou -1)
        b->elevator->currentFloor += 2 * (b->elevator->currentFloor < b->elevator->targetFloor) - 1;
    }
}