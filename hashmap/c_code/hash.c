#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct node{
        char *key;
        char *value;
        struct node *next;
};

//creamos una estructura que sea la hash

struct HashTable{
        int size;
        int count; //permite que crezca el tamaño
        struct node **buckets; //arreglo a los buckets
};


struct HashTable *ht_create(int size){
        struct HashTable *table = (struct HashTable*) malloc(sizeof(struct HashTable));
        table->size=size;
        table->count =0;
        table->buckets=(struct node**)calloc(table->size,sizeof(struct node*));
        return table;
}

unsigned long hash(unsigned char *key){
        unsigned long hash = 5381;
        int c;
        while(c = *key++){
                printf("%d \n", hash);
                printf("c: %c\n", c);
                hash = ((hash << 5) + hash) ^ c;
        }
        return hash;
}


void ht_set(struct HashTable *table, char *key, char *value){
        unsigned long hash_value = hash((unsigned char*)key);
        int index = hash_value % table->size;
        struct node *nodo = table->buckets[index];
        while(nodo!=NULL){
                //strcmp se usa para comparar dos cadenas
                if(strcmp(nodo->key, key)==0){
                        free(nodo->value);
                        nodo->value = strdup(value);
                        return;
                }
                nodo = nodo->next;
        }
        //usamos strdup, que simplimente crea una copia de la cadena asignando memoria dinamicamente
        
        struct node *new_node = (struct node*)malloc(sizeof(struct node));
        new_node -> key = strdup(key);
        new_node->value = strdup(value);
        
        new_node->next = table->buckets[index];
        table->buckets[index] = new_node;
        
}

char *ht_get(struct HashTable *table, char *key){
        
        unsigned long hash_value = hash((unsigned char*)key);
        int index = hash_value%table->size;
        
        struct node *nodo = table->buckets[index];
        
        while(nodo!=NULL){
                if(strcmp(nodo->key, key) ==0){
                        return nodo->value;
                }
                nodo = nodo->next;
        }
        
        return NULL;
        
}


void ht_free(struct HashTable *table){
        for(int i = 0; i<table->size;i++){
                struct node *nodo = table->buckets[i];
                while(nodo!=NULL){
                        struct node *temp = nodo;
                        nodo = nodo->next;
                        free(temp->key);
                        free(temp->value);
                        free(temp);
                }
        }
        free(table->buckets);
        free(table);
}

void ht_delete(struct HashTable *table, char *key){
    if (!table || !key) return;  // Validación NULL
    
    unsigned long hash_value = hash((unsigned char*)key);
    int index = hash_value % table->size;
    
    struct node *current = table->buckets[index];
    struct node *prev = NULL;
    
    while(current != NULL){
        if(strcmp(current->key, key) == 0){
            if(prev == NULL){
                table->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            
            free(current->key);
            free(current->value);
            free(current);
            table->count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}



int main() {
        struct HashTable *ht = ht_create(50);
        
        // Guardamos datos
        ht_set(ht, "nombre", "Anisia");
        ht_set(ht, "profesion", "Programadora");
        
        // Recuperamos y mostramos los datos
        char *nombre = ht_get(ht, "nombre");
        char *profesion = ht_get(ht, "profesion");
        char *apellido = ht_get(ht, "apellido"); // Esta llave no existe
        
        printf("Nombre: %s\n", nombre);
        printf("Profesión: %s\n", profesion);
        
        if (apellido == NULL) {
                printf("El apellido no fue encontrado.\n");
        }
        
        return 0;
}
