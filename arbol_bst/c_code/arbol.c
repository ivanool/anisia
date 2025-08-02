#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct Node{
    char *value;
    struct Node* izquierdo;
    struct Node* derecho;
};

struct Node* crear_nodo(char *value){
    //guardamos el espacio de memoria suficiente para crear un nodo del tamaño de mi estructura
    struct Node* nuevo_nodo = (struct Node*)malloc(sizeof(struct Node));
    nuevo_nodo->value = value;
    nuevo_nodo->izquierdo = NULL;
    nuevo_nodo->derecho = NULL;
    return nuevo_nodo;
}

struct Node* insertar(struct Node* raiz, char *value){
    if(raiz == NULL){
        return crear_nodo(value);
    }

    // Usamos strcmp para comparar el contenido de las cadenas
    int comparacion = strcmp(value, raiz->value);

    if(comparacion < 0){ // 'value' es menor (va antes alfabéticamente)
        raiz->izquierdo = insertar(raiz->izquierdo, value);
    } else if(comparacion > 0){ // 'value' es mayor (va después alfabéticamente)
        raiz->derecho = insertar(raiz->derecho, value);
    }
    
    // Si comparacion es 0, los valores son iguales y no se inserta para evitar duplicados.
    return raiz;
}

void recorrer(struct Node* nodo){
    if(nodo != NULL){
        recorrer(nodo->izquierdo);
        // Añadido un espacio para una salida más limpia
        printf("%s ", nodo->value);
        recorrer(nodo->derecho);
    }
}

// Función principal
int main() {
    struct Node* raiz = NULL;

    printf("Insertando valores en el arbol...\n");
    raiz = insertar(raiz, "g");

    insertar(raiz, "f");
    insertar(raiz, "e");
    insertar(raiz, "d");
    insertar(raiz, "c");
    insertar(raiz, "b");
    insertar(raiz, "a");

    printf("Recorrido 'in-order' del arbol (deberia estar ordenado):\n");
    recorrer(raiz);
    printf("\n");

    return 0;
}