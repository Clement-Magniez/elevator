#include <stdio.h>
#include <stdlib.h>
#include "person.h"

Person* createPerson(int src, int dest)
{
    Person* res = (Person*)malloc(sizeof(Person));
    res->src = src;
    res->dest = dest;
    return res;
}

PersonList* createPersonList(Person* p)
{
    PersonList* res = (PersonList*)malloc(sizeof(PersonList));
    res->person = p;
    res->next = NULL;
    return res;
}

PersonList* insert(Person *p, PersonList *list)
{
    if(list == NULL)
        return createPersonList(p);

    PersonList* res = createPersonList(p);
    res->next = list;
    return res;
}


int length(PersonList* list)
{
    if(list == NULL)
        return 0;
    return 1 + length(list->next);
}