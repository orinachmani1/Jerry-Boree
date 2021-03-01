#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Jerry.h"


Jerry* createJerry(char* id, int hap, Origin* o)
{
	if (id == NULL || hap < 0 || hap > 100 || o == NULL ){return NULL;}

	Jerry* newJerry = (Jerry*)malloc(sizeof(Jerry));
	if (newJerry == NULL){return NULL;}

	newJerry->id= malloc(sizeof(char)*strlen(id)+1);
	if (newJerry->id == NULL)
	{
		free(newJerry);
		newJerry = NULL;
		return NULL;
	}
	strcpy(newJerry->id,id);

	newJerry->numOfAbilities=0;
	//newJerry->jerryAbilities = createLinkedList(shallow_copy, free_shallow, compareAbilities, printAbil);
	newJerry->jerryAbilities=NULL;
	newJerry->happiness = hap;
	newJerry->jerryOrigin = o;

	return newJerry;

}

Planet* createPlanet(char* name, float x, float y ,float z)
{
	if(name ==NULL){return NULL;}

	Planet* newPlanet = malloc(sizeof(Planet));
	if (newPlanet == NULL){return NULL;}

	newPlanet->planetName=malloc(sizeof(char)*strlen(name)+1);
	if (newPlanet->planetName == NULL)
	{
		free(newPlanet);
		newPlanet = NULL;
		return NULL;
	}

	strcpy(newPlanet->planetName,name);

	newPlanet->x = x;
	newPlanet->y = y;
	newPlanet->z = z;
	return newPlanet;

}


Origin* createOrigin(Planet* p, char* n)
{
	if(n == NULL || p == NULL){return NULL;}

	Origin* newOrigin = (Origin*)malloc(sizeof(Origin));
	if (newOrigin == NULL){return NULL;}

	newOrigin->name = malloc(sizeof(char)*strlen(n)+1);
	if (newOrigin->name == NULL)
	{
		free(newOrigin);
		newOrigin = NULL;
		return NULL;
	}
	strcpy(newOrigin->name,n);
	newOrigin->originStar = p;

	return newOrigin;

}


PhysicalChar* createPhysicalChar(char* name, float value)
{
	if(name == NULL || value < 0 ){return NULL;}

	PhysicalChar* newAbility = (PhysicalChar*)malloc(sizeof(PhysicalChar));
	if (newAbility == NULL)
	{
		return NULL;
	}

	newAbility->name = malloc(sizeof(char)*strlen(name)+1);
	if (newAbility->name == NULL)
	{
		free(newAbility);
		newAbility = NULL;
		return NULL;
	}
	strcpy(newAbility->name,name);
	newAbility->val= value;
	return newAbility;
}

bool checkAbility(Jerry* j,char* p)
{
	if(j == NULL || p == NULL){return false;}
	for(int i = 0; i < j->numOfAbilities;i++)
	{
		if(strcmp(j->jerryAbilities[i]->name,p)==0)
		{
			return true;
		}
	}
	return false;

}

status addAbility(Jerry* j,PhysicalChar* p)
{
	if(j == NULL || p == NULL){return fail_mem;}

	int len = j->numOfAbilities;
	bool b =checkAbility(j, p->name);

    if(b==true){return fail_value;} // if the ability already exist

    PhysicalChar** tmp=realloc(j->jerryAbilities,(len+1)*sizeof(p));
    if (tmp == NULL) {return fail_mem;}
    tmp[len]=p;

	//change the at address parameter
    j->jerryAbilities=tmp;
    j->numOfAbilities++;
	return success;
}

status delAbility(Jerry* j, char* name)
{
	if(j == NULL || name == NULL){return fail_mem;}
	int found = 0;
	bool b = checkAbility(j, name);
	if (b == false){return fail_value;}
	int len = j->numOfAbilities;
	PhysicalChar** tmp;
	if (len > 1){ // make sure we don't allocate size of zero.
		tmp = malloc((len-1)*sizeof(PhysicalChar*));
		if (tmp == NULL) {return fail_mem;}
	}
	for(int i=0; i < j->numOfAbilities; i++)
	{
		if(strcmp(j->jerryAbilities[i]->name,name)==0)
		{
			distPhysicalChar(j->jerryAbilities[i]);
			found = 1;
		}

		else
		{
			tmp[i-found] = j->jerryAbilities[i];
		}
	}
	free(j->jerryAbilities);
	j->jerryAbilities=tmp;
	j->numOfAbilities--;
	return success;
}

float get_ability_val(Jerry* jer, char* ability){
    if(jer == NULL || ability == NULL){return 0;}
    for(int i = 0; i < jer->numOfAbilities;i++)
    {
        if(strcmp(jer->jerryAbilities[i]->name,ability)==0)
        {
            return jer->jerryAbilities[i]->val;
        }
    }
    return 0.0;
}

status printJerry(Jerry* j)
{
	if (j == NULL) { return fail_mem;}
	printf("Jerry , ID - %s : \n", j->id);
	printf("Happiness level : %d \n", j->happiness);
	printf("Origin : %s \n", j->jerryOrigin->name);
	printPlanet(j->jerryOrigin->originStar);
	if(j->numOfAbilities > 0)
	{
		printf("Jerry's physical Characteristics available : \n");
	}

	for(int i = 0; i< j->numOfAbilities; i++)
	{
		if(i==0)
		{
			printf("\t%s : %.2f", j->jerryAbilities[i]->name,j->jerryAbilities[i]->val);

		}
		else
		{
			printf(" , %s : %.2f",j->jerryAbilities[i]->name,j->jerryAbilities[i]->val);
		}

	}
	if (j->numOfAbilities > 0){
		printf(" \n");
	}
	return success;

}

status printPlanet(Planet* p)
{
	if (p == NULL) { return fail_mem;}
	printf("Planet : %s (%.2f,%.2f,%.2f) \n", p->planetName, p->x,p->y,p->z);
	return success;
}

void distPlanet(Planet* p)
{
	if (p == NULL) {return;}
	free(p->planetName);
	p->planetName=NULL;
	free(p);
	p=NULL;
}

void distOrigin(Origin* o)
{
	if (o == NULL) {return;}
	free(o->name);
	o->name = NULL;
	free(o);
	//we will not destroy planet here, because it might be referenced by another origin
}

void distPhysicalChar(PhysicalChar* p)
{
	if (p == NULL) {return;}
	free(p->name);
	p->name = NULL;
	free(p);
}

void distJerry(Jerry* j)
{
	if (j == NULL) { return;}
	free(j->id);
	j->id = NULL;

	distOrigin(j->jerryOrigin);

	for(int i = 0; i < j->numOfAbilities; i++)
	{
		distPhysicalChar(j->jerryAbilities[i]);
	}
	if (j->numOfAbilities > 0)
	{
		free(j->jerryAbilities);
	}
	free(j);
}

Planet* get_planet_by_name(char* name, LinkedList planets_list){
	if (planets_list == NULL) {return NULL;}
	Planet dummy_planet;
	dummy_planet.planetName = name;

	return searchByKeyInList(planets_list, &dummy_planet);
}

status print_all_jerries(LinkedList jerries_list)
{
	if (NULL == jerries_list) { return fail_mem;}
	displayList(jerries_list);
	return success;
}

status print_all_planets(LinkedList planets_list)
{
	if (NULL == planets_list) { return fail_mem;}
	displayList(planets_list);
	return success;
}

Jerry* get_jerry_by_id(hashTable jerries_by_name, char* id){
    return lookupInHashTable(jerries_by_name, id);
}
bool comparePlanets(Planet* planetA, Planet* planetB){
    return 0 == strcmp(planetA->planetName, planetB->planetName);
}

bool compareJerries(Jerry* jerryA, Jerry* jerryB){
    return 0 == strcmp(jerryA->id, jerryB->id);
}

bool compareAbilities(PhysicalChar* phys1, PhysicalChar* phys2)
{
    return 0 == strcmp(phys1->name, phys2->name);
}

status printAbil(PhysicalChar* p){
    printf("%s : %.2f , ",p->name, p->val);
    return success;

}


int getHappines(Element elem)
{
	if (elem == NULL ){return -1;}
	Jerry* j = (Jerry*)elem;
	if (j == NULL ){return failure;}

	return j->happiness;
}
status add_happines_to_Jerry(Element elem, int n)
{
	if (elem == NULL ){return failure;}
	Jerry* j = (Jerry*)elem;
	if (j == NULL ){return failure;}

	int currHappines = j->happiness;
	if (n + currHappines <= 100)
	{
		j->happiness = n + currHappines;
		return success;
	}
	j->happiness = 100;
	return success;
}
status sub_happines_from_Jerry(Element elem, int n)
{
	if (elem == NULL ){return failure;}
	Jerry* j = (Jerry*)elem;
	if (j == NULL ){return failure;}

	int currHappines = j->happiness;
	if (currHappines - n >= 0)
	{
		j->happiness = currHappines - n;
		return success;
	}
	j->happiness = 0;
	return success;
}

