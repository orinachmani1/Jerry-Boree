#include <math.h>
#include "Jerry.h"
#include "Defs.h"
#include "LinkedList.h"
#include "MultiValueHashTable.h"



Planet* line_to_planet(char* line_buffer){
// Find planet name
    char planet_name[300];
    int j = 0;
    char* line_traveler = line_buffer;
    while(*line_traveler != ','){
        planet_name[j] = *line_traveler;
        j++;
        line_traveler++;
    }
    planet_name[j] = '\0';
    // Find x,y,z cordinates
    line_traveler++;
    j = 0;
    char x_cord[300];
    while(*line_traveler != ','){
        x_cord[j] = *line_traveler;
        j++;
        line_traveler++;
    }
    x_cord[j] = '\0';
    line_traveler++;
    j = 0;
    char y_cord[300];
    while(*line_traveler != ','){
        y_cord[j] = *line_traveler;
        j++;
        line_traveler++;
    }
    y_cord[j] = '\0';
    line_traveler++;
    j = 0;
    char z_cord[300];
    while(*line_traveler != '\n'){
        z_cord[j] = *line_traveler;
        j++;
        line_traveler++;
    }
    z_cord[j] = '\0';
    return createPlanet(planet_name, atof(x_cord), atof(y_cord) ,atof(z_cord));
}

Jerry* line_to_jerry(char* line_buffer, LinkedList planets_list){
// Find planet name
    char id[300];
    int j = 0;
    char* line_traveler = line_buffer;
    while(*line_traveler != ','){
        id[j] = *line_traveler;
        j++;
        line_traveler++;
    }
    id[j] = '\0';
    // Find x,y,z cordinates
    line_traveler++;
    j = 0;
    char origin_name[300];
    while(*line_traveler != ','){
        origin_name[j] = *line_traveler;
        j++;
        line_traveler++;
    }
    origin_name[j] = '\0';
    line_traveler++;
    j = 0;
    char planet_name[300];
    while(*line_traveler != ','){
        planet_name[j] = *line_traveler;
        j++;
        line_traveler++;
    }
    planet_name[j] = '\0';
    line_traveler++;
    j = 0;
    char happines[300];
    while(*line_traveler != '\n'){
        happines[j] = *line_traveler;
        j++;
        line_traveler++;
    }
    happines[j] = '\0';
    Planet* plan_for_origin = get_planet_by_name(planet_name, planets_list);
    if (plan_for_origin == NULL) {return NULL;}
    Origin* jer_origin = createOrigin(plan_for_origin, origin_name);
    if (jer_origin == NULL) {return NULL;}
    Jerry* jer = createJerry(id, atoi(happines), jer_origin);
    return jer;
}

PhysicalChar* line_to_ability(char* line_buffer){
    char ab_name[300];
    int j = 0;
    char* line_traveler = line_buffer;
    line_traveler++;
    while(*line_traveler != ':'){
        ab_name[j] = *line_traveler;
        j++;
        line_traveler++;
    }
    ab_name[j] = 0;
    line_traveler++;
    j = 0;
    char ab_val[300];
    while(*line_traveler != '\n'){
        ab_val[j] = *line_traveler;
        j++;
        line_traveler++;
    }
    ab_val[j] = 0;
    return createPhysicalChar(ab_name, atof(ab_val));
}


char* get_line_from_user(char* output_buffer, int buffer_size){
    fgets(output_buffer, buffer_size, stdin);
    char* p = output_buffer;
    while(*p != '\n'){
        p++;
    }
    *p = '\0';
    return output_buffer;
}

status add_char(LinkedList jerries_list, hashTable jerries_by_name, multiValueHashTable jerrys_by_abil){
    if (jerries_list == NULL) { return fail_mem; }
    printf("What is your Jerry's ID ? \n");
    char id[300];
    // first time flush the \n from stdin
    fgets(id, sizeof(id), stdin);
    get_line_from_user(id, sizeof(id));
    Jerry* relevant_jerry = get_jerry_by_id(jerries_by_name, id);
    if (relevant_jerry == NULL){
        printf("Rick this Jerry is not in the daycare ! \n");
        return fail_value;
    }
    printf("What physical characteristic can you add to Jerry - %s ? \n", id);
    char char_name[300];
    get_line_from_user(char_name, sizeof(char_name));
    if (true ==  checkAbility(relevant_jerry, char_name))
    {
        printf("The information about his %s already available to the daycare ! \n", char_name);
        return fail_value;
    }

    char char_val[300];
    printf("What is the value of his %s ? \n", char_name);
    get_line_from_user(char_val, sizeof(char_val));
    PhysicalChar* characteristic = createPhysicalChar(char_name, atof(char_val));
    if (characteristic == NULL) { return fail_mem;}
    status abi_status = addAbility(relevant_jerry, characteristic);
    if (success == abi_status)
    {
        addToMultiValueHashTable(jerrys_by_abil, char_name, relevant_jerry);
        LinkedList JerriesWithSameAbil = lookupInMultiValueHashTable(jerrys_by_abil, char_name);
        printf("%s : \n", char_name);
        displayList(JerriesWithSameAbil);

    }
    return abi_status;
}


status remove_char(LinkedList jerries_list, hashTable jerries_by_name, multiValueHashTable jerrys_by_abil)
{
    if (jerries_list == NULL) { return fail_mem; }
    printf("What is your Jerry's ID ? \n");
    char id[300];
    // first time flush the \n from stdin
    fgets(id, sizeof(id), stdin);
    get_line_from_user(id, sizeof(id));
    Jerry* relevant_jerry = get_jerry_by_id(jerries_by_name, id);
    if (relevant_jerry == NULL){
        printf("Rick this Jerry is not in the daycare ! \n");
        return fail_value;
    }
    printf("What physical characteristic do you want to remove from Jerry - %s ? \n", id);
    char char_name[300];
    get_line_from_user(char_name, sizeof(char_name));
    if (false ==  checkAbility(relevant_jerry, char_name))
    {
        printf("The information about his %s not available to the daycare ! \n", char_name);
        return fail_value;
    }
    status st = removeFromMultiValueHashTable(jerrys_by_abil, char_name, relevant_jerry);
    if (success != st){
        return st;
    }

    st = delAbility(relevant_jerry, char_name);
    if (success == st)
    {
        printJerry(relevant_jerry);
    }
    return st;
}

status get_jerry_out_of_sys(Jerry* relevant_jerry,LinkedList jerries_list,
                            hashTable jerries_by_name, multiValueHashTable jerrys_by_abil)
{
    status st;
    for (int i = 0; i < relevant_jerry->numOfAbilities; i++){
        char* char_name = relevant_jerry->jerryAbilities[i]->name;
        st = removeFromMultiValueHashTable(jerrys_by_abil, char_name, relevant_jerry);
        if (success != st){
            return st;
        }
    }
    st = removeFromHashTable(jerries_by_name, relevant_jerry->id);
    if (success != st){
        return st;
    }
    st = deleteNode(jerries_list, relevant_jerry);
    if (success == st)
    {
        printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    }
    return st;
}

status remove_jerry(LinkedList jerries_list, hashTable jerries_by_name, multiValueHashTable jerrys_by_abil)
{
    if (jerries_list == NULL) { return fail_mem; }
    printf("What is your Jerry's ID ? \n");
    char id[300];
    // first time flush the \n from stdin
    fgets(id, sizeof(id), stdin);
    get_line_from_user(id, sizeof(id));
    Jerry* relevant_jerry = get_jerry_by_id(jerries_by_name, id);
    if (relevant_jerry == NULL){
        printf("Rick this Jerry is not in the daycare ! \n");
        return fail_value;
    }

    return get_jerry_out_of_sys(relevant_jerry, jerries_list, jerries_by_name, jerrys_by_abil);

}


status get_similar_jerry(LinkedList jerries_list, hashTable jerries_by_name, multiValueHashTable jerrys_by_abil){
    if (jerries_list == NULL) { return fail_mem; }
    printf("What do you remember about your Jerry ? \n");
    char character[300];
    // first time flush the \n from stdin
    fgets(character, sizeof(character), stdin);
    get_line_from_user(character, sizeof(character));
    LinkedList jerries_with_char = lookupInMultiValueHashTable(jerrys_by_abil, character);
    if (NULL == jerries_with_char){
        printf("Rick we can not help you - we do not know any Jerry's %s ! \n", character);
        return fail_value;
    }
    char char_val[300];
    printf("What do you remember about the value of his %s ? \n", character);
    get_line_from_user(char_val, sizeof(char_val));
    float char_remember = atof(char_val);
    int num_of_pot_jerries = getLengthList(jerries_with_char);
    float min_dist = 99999999.0;
    Node current_node = getHead(jerries_with_char);
    Jerry* closest_jer = NULL;
    for (int i =0; i < num_of_pot_jerries; ++i){
        Jerry* current_jerry = getVal(current_node);
        float curr_char_val = get_ability_val(current_jerry, character);
        if (fabs(curr_char_val - char_remember) < min_dist ){
            closest_jer = current_jerry;
            min_dist = fabs(curr_char_val - char_remember);
        }
        current_node = getNext(current_node);
    }
    printf("Rick this is the most suitable Jerry we found : \n");
    printJerry(closest_jer);
    return get_jerry_out_of_sys(closest_jer, jerries_list, jerries_by_name, jerrys_by_abil);


}

// handle memory cleanup
void cleanup(LinkedList planets_list,  LinkedList jerries_list, hashTable jerries_by_name,
             multiValueHashTable jerries_by_char,status ret_status)
{
    destroyMultiValueHashTable(jerries_by_char);
    destroyHashTable(jerries_by_name);
    destroyList(planets_list);
    destroyList(jerries_list);
    printf("The daycare is now clean and close ! \n");
    exit(ret_status);
}

///////  1 - in menu
status take_jerry(LinkedList jerries_list, LinkedList planets_list, hashTable jerries_by_name){
    if (jerries_list == NULL) { return fail_mem; }
    printf("What is your Jerry's ID ? \n");
    char id[300];
    // first time flush the \n from stdin
    fgets(id, sizeof(id), stdin);
    get_line_from_user(id, sizeof(id));
    if (NULL != get_jerry_by_id(jerries_by_name, id)){
        printf("Rick did you forgot ? you already left him here ! \n");
        return fail_value;
    }
    printf("What planet is your Jerry from ? \n");
    char plan_name[300];
    get_line_from_user(plan_name, sizeof(plan_name));
    Planet* plan_for_origin = get_planet_by_name(plan_name, planets_list);
    if (NULL == plan_for_origin){
        printf("%s is not a known planet ! \n", plan_name);
        return fail_value;
    }
    printf("What is your Jerry's dimension ? \n");
    char dim[300];
    get_line_from_user(dim, sizeof(dim));
    Origin* jer_origin = createOrigin(plan_for_origin, dim);

    printf("How happy is your Jerry now ? \n");
    char happ[300];
    get_line_from_user(happ, sizeof(happ));
    Jerry* new_jerry = createJerry(id, atoi(happ), jer_origin);

    status st = appendNode(jerries_list, new_jerry);
    if (success != st) {return st;}

    st = addToHashTable(jerries_by_name, id, new_jerry);
    if (success != st) {return st;}
    printJerry(new_jerry);
    return st;


}


char *copy_key(char *key) {
    char* new_key = malloc(strlen(key) + 1);
    return strcpy(new_key, key);
}

status free_key(char *key) {
    free(key);
    return success;
}

status print_key(char *key) {
    printf("%s\n", key);
    return success;
}

Element shallow_copy(Element input)
{
    return input;
}

status free_shallow(Element key) {
    return success;
}

bool equal_keys(char *keyA, char *keyB) {
    return 0 == strcmp(keyA, keyB);
}

int ascii_sum_of_string(char* string){
    char* p = string;
    int sum = 0;
    while('\0' != *p){
        sum += *p;
        p++;
    }
    return sum;
}

status saddest_jerry(LinkedList jerries_list, hashTable jerries_by_name, multiValueHashTable jerrys_by_abil){
    if (jerries_list == NULL) { return fail_mem; }
    if (getLengthList(jerries_list) < 1)
    {
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return failure;
    }

    Node current_node = getHead(jerries_list);
    Jerry* closest_jer = NULL;
    int min_happines = 101;

    for (int i = 0; i < getLengthList(jerries_list); ++i)
    {
        Jerry* current_jerry = getVal(current_node);
        int happinesLevel = current_jerry->happiness ;
        if (happinesLevel < min_happines )
        {
            min_happines = happinesLevel;
            closest_jer = current_jerry;
        }
        current_node = getNext(current_node);
    }
    printf("Rick this is the most suitable Jerry we found : \n");
    printJerry(closest_jer);

    return get_jerry_out_of_sys(closest_jer, jerries_list, jerries_by_name, jerrys_by_abil);



}

int main(int argc, char* argv[])
{
    if (argc != 3){
        return failure;
    }
    int bufferLength = 300;
    char line_buffer[bufferLength];
    int num_of_planets = atoi(argv[1]);
    char* filename = argv[2];
    int num_of_jerries = 0;
    FILE* filePointer;

    LinkedList planets_list = createLinkedList(shallow_copy, (FreeFunction) distPlanet, (EqualFunction) comparePlanets,
                                               (PrintFunction) printPlanet);
    if (planets_list == NULL) { return fail_mem;}
    LinkedList jerries_list = createLinkedList(shallow_copy, (FreeFunction) distJerry, (EqualFunction) compareJerries,
                                               (PrintFunction) printJerry);
    if (jerries_list == NULL) {
        destroyList(planets_list);
        return fail_mem;
    }

    multiValueHashTable jerries_by_physical = createMultiValueHashTable(
            (CopyFunction) copy_key, (FreeFunction) free_key, (PrintFunction) print_key,
            shallow_copy, free_shallow, (PrintFunction) printJerry,
            (EqualFunction) equal_keys, (EqualFunction) compareJerries,
            (TransformIntoNumberFunction) ascii_sum_of_string, 11); //to complite..


    hashTable jerries_by_name = createHashTable(
            (CopyFunction) copy_key, (FreeFunction) free_key, (PrintFunction) print_key,
            shallow_copy, free_shallow, (PrintFunction) printJerry,
            (EqualFunction)equal_keys, (TransformIntoNumberFunction) ascii_sum_of_string, 11);


    filePointer = fopen(filename, "r");
    char* read = fgets(line_buffer, bufferLength, filePointer);
    if (read == NULL || strcmp(line_buffer, "Planets\n") != 0)
    {
        return failure;
    }
    for (int i = 0; i < num_of_planets; ++i){
        read = fgets(line_buffer, bufferLength, filePointer);
        Planet* new_plan = line_to_planet(line_buffer);
        if (NULL == new_plan)
        {
            return failure;
        }
        status st = appendNode(planets_list, new_plan);
        if (success != st)
        {
            return failure;
        }

    }
    read = fgets(line_buffer, bufferLength, filePointer);
    if (read == NULL || strcmp(line_buffer, "Jerries\n") != 0)
    {
        return failure;
    }
    Jerry* current_jerry = NULL;
    while (fgets(line_buffer, bufferLength, filePointer)) {
        if (line_buffer[0] == '\n') {continue;} // finished the file
        if (line_buffer[0] == '\t'){
            PhysicalChar* abil = line_to_ability(line_buffer);
            status st = addAbility(current_jerry, abil);
            addToMultiValueHashTable(jerries_by_physical, abil->name, current_jerry);
            if (st != success) {
                return failure;
            }
        }
        else
        {
            current_jerry = line_to_jerry(line_buffer, planets_list);
            if (NULL == current_jerry)
            {
                return failure;
            }
            status st = appendNode(jerries_list, current_jerry);
            if (success != st)
            {
                return failure;
            }
            addToHashTable(jerries_by_name, current_jerry->id, current_jerry);
        }
    }
    fclose(filePointer);




    // ****** after file
    char ch[20]= " ";
    char cha[20]=" ";
    char c[20] = " ";
    char physicalName[20]=" ";

    while(ch[0]!='9')
    {
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");
        scanf("%s", ch);
        if (ch[1] != '\0')
        {
            printf("Rick this option is not known to the daycare ! \n");
            continue;
        }
        switch(ch[0])
        {
            case '1':
                take_jerry(jerries_list, planets_list, jerries_by_name);
                break;

            case '2':
                add_char(jerries_list, jerries_by_name, jerries_by_physical);
                break;

            case '3':
                remove_char(jerries_list, jerries_by_name, jerries_by_physical);
                break;

            case '4':
                remove_jerry(jerries_list, jerries_by_name, jerries_by_physical);
                break;
            case '5':
                get_similar_jerry(jerries_list, jerries_by_name, jerries_by_physical);
                break;
            case '6':
                saddest_jerry(jerries_list,jerries_by_name,jerries_by_physical);
                break;

            case '7':
                do{
                    printf("What information do you want to know ? \n");
                    printf("1 : All Jerries \n");
                    printf("2 : All Jerries by physical characteristics \n");
                    printf("3 : All known planets \n");
                    scanf("%s", cha);
                    if (cha[1] != '\0')
                    {
                        printf("Rick this option is not known to the daycare ! \n");
                        continue;
                    }
                    switch(cha[0])
                    {
                        case '1':
                            if(getLengthList(jerries_list) < 1)
                            {
                                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                                break;
                            }
                            print_all_jerries(jerries_list);
                            break;

                        case '2':

                            printf("What physical characteristics ? \n");
                            scanf("%s", physicalName);
                            LinkedList ls = lookupInMultiValueHashTable(jerries_by_physical, physicalName);
                            if(ls == NULL)
                            {
                                printf("Rick we can not help you - we do not know any Jerry's %s ! \n", physicalName);
                                break;
                            }
                            printf("%s : \n", physicalName);
                            displayList(ls);
                            break;

                        case '3':
                            print_all_planets(planets_list);
                            break;

                        default:
                        {
                            printf("Rick this option is not known to the daycare ! \n");
                            break;
                        }
                    }
                }while(0);
                break;

            case '8':
                do{
                    if(getLengthList(jerries_list)<1)
                    {
                    	printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        break;
                    }
                    printf("What activity do you want the Jerries to partake in ? \n");
                    printf("1 : Interact with fake Beth \n");
                    printf("2 : Play golf \n");
                    printf("3 : Adjust the picture settings on the TV \n");
                    scanf("%s", c);
                    if (c[1] != '\0')
                    {
                        printf("Rick this option is not known to the daycare ! \n");
                        continue;
                    }
                    switch(c[0])
                    {
                        case '1':
                            for (int i = 0; i <= getLengthList(jerries_list); i ++)
                            {
                                Element jer = getDataByIndex(jerries_list, i);
                                if (getHappines(jer) >= 20)
                                {
                                    add_happines_to_Jerry(jer,15);
                                }
                                else
                                {
                                    sub_happines_from_Jerry(jer,5);
                                }
                            }
                            printf("The activity is now over ! \n");
                            print_all_jerries(jerries_list);
                            break;
                        case '2':
                            for (int i = 0; i < getLengthList(jerries_list); i ++)
                            {
                                Element jer = getDataByIndex(jerries_list, i);
                                if (getHappines(jer) >= 50)
                                {
                                    add_happines_to_Jerry(jer,10);
                                }
                                else
                                {
                                    sub_happines_from_Jerry(jer,10);
                                }
                            }
                            printf("The activity is now over ! \n");
                            print_all_jerries(jerries_list);
                            break;
                        case '3':
                            for (int i = 0; i < getLengthList(jerries_list); i ++)
                            {
                                Element jer = getDataByIndex(jerries_list, i);
                                add_happines_to_Jerry(jer,20);

                            }
                            printf("The activity is now over ! \n");
                            print_all_jerries(jerries_list);
                            break;
                        default:
                        {
                            printf("Rick this option is not known to the daycare ! \n");
                            break;
                        }
                    }
                }while(0);
                break;

            default:
            {
                if(ch[0]!='9')
                {
                    printf("Rick this option is not known to the daycare ! \n");
                }
                break;
            }
        }
    }


    cleanup(planets_list, jerries_list, jerries_by_name, jerries_by_physical, success);
    return failure;

}
