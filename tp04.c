#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int TareaID;
    char *descripcion;
    int duracion;
}Tarea;

typedef struct{
    Tarea T;
    Nodo *siguiente;
}Nodo;



int main (){

    srand(time(NULL));

    return 0;
}

Nodo *CrearNodo(int id, const char *descripcion, int duracion) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->T.TareaID = id;
    nuevo->T.descripcion = (char *)malloc(strlen(descripcion) + 1);
    strcpy(nuevo->T.descripcion, descripcion);
    nuevo->T.duracion = duracion;
    nuevo->siguiente = NULL;
    return nuevo;
}