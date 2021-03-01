#ifndef JERRY_H_
#define JERRY_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Defs.h"
#include "LinkedList.h"
#include "HashTable.h"


typedef struct planet_t
{
    char* planetName;
    float x;
    float y;
    float z;
}Planet;

typedef struct origin_t
{
    Planet* originStar;
    char* name;
}Origin;

typedef struct PhysicalCharacteristics_t
{
	char* name;
	float val;
}PhysicalChar;

typedef struct Jerry_t
{
    char* id;
    int happiness;
    Origin* jerryOrigin;
    //LinkedList jerryAbilities;
    PhysicalChar** jerryAbilities;
    int numOfAbilities;
}Jerry;

// Jerry functions, create, retrieve, prints and destroy.

Jerry* createJerry(char* id, int hap, Origin* o);
Jerry* get_jerry_by_id(hashTable jerries_by_name, char* id);
status printJerry(Jerry* j);
status print_all_jerries(LinkedList jerries_list);
void distJerry(Jerry* j);
bool compareJerries(Jerry* jerryA, Jerry* jerryB);

// Jerry's ability function, check, add and delete.
bool checkAbility(Jerry* j,char* p);
status addAbility(Jerry* j,PhysicalChar* p);
status delAbility(Jerry* j, char* name);
bool compareAbilities(PhysicalChar* phys1, PhysicalChar* phys2);
status printAbil(PhysicalChar* p);
float get_ability_val(Jerry* jer, char* ability);

// planet functions, create, retrieve print and destroy
Planet* createPlanet(char* name, float x, float y ,float z);
Planet* get_planet_by_name(char* name, LinkedList planets_list);
status printPlanet(Planet* p);
status print_all_planets(LinkedList planets_list);
void distPlanet(Planet* p);
bool comparePlanets(Planet* planetA, Planet* planetB);

// Origin functions create and destroy
Origin* createOrigin(Planet* p, char* n);
void distOrigin(Origin* o);

// physical char functions create and destroy
PhysicalChar* createPhysicalChar(char* name, float value);
void distPhysicalChar(PhysicalChar* p);

int getHappines(Element elem);
status add_happines_to_Jerry(Element elem, int n);
status sub_happines_from_Jerry(Element elem, int n);


#endif /* JERRY_H_ */
