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

Nodo *CrearNodo(int id, const char *descripcion, int duracion);
Nodo *CargarTareasPendientes();
void InsertarNodo(Nodo ** lista, Nodo *nuevo);

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

void InsertarNodo(Nodo ** lista, Nodo *nuevo) {
    nuevo->siguiente = *lista;
    *lista = nuevo;
}

Nodo *CargarTareasPendientes() {
    Nodo *lista = NULL;
    int idAuto = 1000;
    char descripcion[100];
    char opcion;

    do {
        printf("Ingresar descripcion de la tarea: ");
        fflush(stdin);
        fgets(descripcion, sizeof(descripcion), stdin);

        int duracion = 10 + rand() % 91;

        Nodo *nuevo = CrearNodo(idAuto++, descripcion, duracion);
        InsertarNodo(&lista, nuevo);

        printf("Tarea cargada con duracion de: %d minutos", duracion);
        printf("\nDesea cargar otra tarea? (s/n): ");
        scanf(" %c", &opcion);
    }
    while (opcion == 's' || opcion == 'S');
    return lista;
}

Nodo *QuitarTarea(Nodo ** lista, int id){
    Nodo *actual = lista;
    Nodo *anterior = NULL;

    while(actual != NULL && actual->T.TareaID != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (actual == NULL){
        return NULL;
    }
    if (anterior == NULL)
    {
        *lista = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    actual->siguiente = NULL;
    return actual;
}