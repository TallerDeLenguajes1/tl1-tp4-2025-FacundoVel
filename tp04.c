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
void InsertarNodo(Nodo ** lista, Nodo *nuevo);
Nodo *CargarTareasPendientes();
Nodo *QuitarTarea(Nodo ** lista, int id);
Nodo *CrearListaVacia();

int main (){

    srand(time(NULL));
    Nodo *TareasPendientes = CrearListaVacia();
    Nodo *TareasRealizadas = CrearListaVacia();


    return 0;
}

Nodo *CrearListaVacia(){
    return NULL;
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

    if (anterior == NULL){
        *lista = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    actual->siguiente = NULL;
    return actual;
}

void MostrarLista(Nodo *lista) {
    Nodo *auxiliar = lista;
    if (!auxiliar) {
        printf("Lista vacía.\n");
        return;
    }

    while (auxiliar != NULL) {
        printf("ID: %d | Descripción: %s | Duración: %d minutos\n",
               auxiliar->T.TareaID,
               auxiliar->T.descripcion,
               auxiliar->T.duracion);
        auxiliar = auxiliar->siguiente;
    }
}

void TransferirTareas(Nodo **TareasPendientes, Nodo **TareasRealizadas) {
    char opcion;
    int id;

    do {
        printf("\nTareas pendientes actuale: \n");
        MostrarLista(*TareasPendientes);

        if(*TareasPendientes == NULL) {
            printf("No hay tareas pendientes\n");
            return;
        }
        printf("Ingrese el ID de la tarea realizada: ");
        scanf("%d", &id);
        Nodo *mover = QuitarTarea(TareasPendientes, id);

        if(mover != NULL) {
            InsertarNodo(TareasRealizadas, mover);
            printf("\nTarea de ID: %d movida a tareas realizadas, id");
        } else {
            printf("No se encontró la tarea con ID: %d\n", id);
        }
        printf("\nMas tareas realizadas? (s/n): ");

    }while(opcion == 's' || opcion == 'S');

}

void LiberarLista(Nodo *lista) {
    Nodo *auxiliar;
    while (lista != NULL) {
        auxiliar = lista;
        lista = lista->siguiente;
        free(auxiliar->T.descripcion);
        free(auxiliar);
    }
}