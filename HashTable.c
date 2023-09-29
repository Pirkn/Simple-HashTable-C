#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFFFFFFUL)

typedef struct{
    char name[MAX_NAME];
    int age;
} person;

person* hash_table[TABLE_SIZE];

unsigned int hash(char *name){
    int lenght = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for(int i = 0; i < lenght; i++){
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table(){
    for(int i = 0; i < TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
}

void print_table(){
    for(int i = 0; i < TABLE_SIZE; i++){
        if(hash_table[i] == NULL){
            printf("\t%d\t----\n", i);
        } else if(hash_table[i] == DELETED_NODE){
            printf("\t%d\t----\n", i);
        } else{
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
}

bool hash_table_insert(person *p){
    if(p == NULL) return false;
    int index = hash(p->name);
    for(int i = 0; i < TABLE_SIZE; i++){
        int try = (i + index) % TABLE_SIZE;
        if(hash_table[try] == NULL || 
            hash_table[try] == DELETED_NODE){
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

person *hash_table_lookup(char *name){
    int index = hash(name);
    for(int i = 0; i < TABLE_SIZE; i++){
        int try = (index + i) % TABLE_SIZE;
        if(hash_table[try] == NULL){
            return false;
        }
        if(hash_table[try] == DELETED_NODE) continue;
        if(strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0){
            return hash_table[index];
        }
    }
    return NULL;
}

person *hash_table_delete(char *name){
    int index = hash(name);
    for(int i = 0; i < TABLE_SIZE; i++){
        int try = (index + i) % TABLE_SIZE;
        if(hash_table[try] == NULL){
            return NULL;
        }
        if(hash_table[try] == DELETED_NODE) continue;
        if(strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0){
            person *tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }
    return NULL;
}

int main(){

    init_hash_table();

    person jacob = {.name="Jacob", .age =256};
    person kate = {.name="Kate", .age =27};
    person mpho = {.name="Mpho", .age =25};
    person sarah = {.name="Sarah", .age =54};
    person maren = {.name="Maren", .age =15};
    person edna = {.name="Edna", .age =24};
    person eliza = {.name="Eliza", .age =31};
    person robert = {.name="Robert", .age =2};
    person jane = {.name="Jane", .age =7};

    hash_table_insert(&jacob);
    hash_table_insert(&kate);
    hash_table_insert(&mpho);
    hash_table_insert(&sarah);
    hash_table_insert(&maren);
    hash_table_insert(&edna);
    hash_table_insert(&eliza);
    hash_table_insert(&robert);
    hash_table_insert(&jane);

    print_table();

    person* tmp = hash_table_lookup("Mpho");
    if(tmp == NULL){
        printf("Person not found!\n");
    } else{
        printf("%s`s age is: %d.\n", tmp->name, tmp->age);
    }

    tmp = hash_table_lookup("George");
    if(tmp == NULL){
        printf("Person not found!\n");
    } else{
        printf("%s`s age is: %d.\n", tmp->name, tmp->age);
    }

    hash_table_delete("Mpho");

    tmp = hash_table_lookup("Mpho");
    if(tmp == NULL){
        printf("Person not found!\n");
    } else{
        printf("%s`s age is: %d.\n", tmp->name, tmp->age);
    }

    return 0;
}