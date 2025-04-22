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
void InsertarNodo(Nodo **lista, Nodo *nuevo);
Nodo *CargarTareasPendientes();
Nodo *QuitarTarea(Nodo **lista, int id);
Nodo *CrearListaVacia();
void MostrarLista(Nodo *lista);
void TransferirTareas(Nodo **TareasPendientes, Nodo **TareasRealizadas);
void LiberarLista(Nodo *lista);
void ConsultarTarea(Nodo *pendientes, Nodo *realizadas, int id, const char *palabra);

int main (){

    srand(time(NULL));

    Nodo *TareasPendientes = CrearListaVacia();
    Nodo *TareasRealizadas = CrearListaVacia();

    TareasPendientes = CargarTareasPendientes();

    TransferirTareas(&TareasPendientes, &TareasRealizadas);

    printf("\nTAREAS PENDIENTES:\n");
    MostrarLista(TareasPendientes);

    printf("\nTAREAS REALIZADAS:\n");
    MostrarLista(TareasRealizadas);

    int idBuscado = 1000;
    char palabraClave[100] = "cor";
    ConsultarTarea(TareasPendientes, TareasRealizadas, idBuscado, palabraClave);

    LiberarLista(TareasPendientes);
    LiberarLista(TareasRealizadas);

    return 0;


    return 0;
}
Nodo *CrearListaVacia() {
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

void InsertarNodo(Nodo **lista, Nodo *nuevo) {
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
        descripcion[strcspn(descripcion, "\n")] = '\0';

        int duracion = 10 + rand() % 91;

        Nodo *nuevo = CrearNodo(idAuto++, descripcion, duracion);
        InsertarNodo(&lista, nuevo);

        printf("Tarea cargada con duracion de: %d minutos\n", duracion);
        printf("Desea cargar otra tarea? (s/n): ");
        scanf(" %c", &opcion);
        getchar();
    } while (opcion == 's' || opcion == 'S');

    return lista;
}

Nodo *QuitarTarea(Nodo **lista, int id) {
    Nodo *actual = *lista;
    Nodo *anterior = NULL;

    while (actual != NULL && actual->T.TareaID != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return NULL;
    }

    if (anterior == NULL) {
        *lista = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    actual->siguiente = NULL;
    return actual;
}

void MostrarLista(Nodo *lista) {
    Nodo *aux = lista;
    if (!aux) {
        printf("Lista vacia.\n");
        return;
    }
    while (aux != NULL) {
        printf("ID: %d | Descripcion: %s | Duracion: %d minutos\n",
               aux->T.TareaID,
               aux->T.descripcion,
               aux->T.duracion);
        aux = aux->siguiente;
    }
}

void TransferirTareas(Nodo **TareasPendientes, Nodo **TareasRealizadas) {
    char opcion;
    int id;

    do {
        printf("\nTareas pendientes actuales:\n");
        MostrarLista(*TareasPendientes);

        if (*TareasPendientes == NULL) {
            printf("No hay tareas pendientes\n");
            return;
        }

        printf("Ingrese el ID de la tarea realizada: ");
        scanf("%d", &id);
        Nodo *mover = QuitarTarea(TareasPendientes, id);

        if (mover != NULL) {
            InsertarNodo(TareasRealizadas, mover);
            printf("Tarea de ID: %d movida a tareas realizadas.\n", id);
        } else {
            printf("No se encontro la tarea con ID: %d\n", id);
        }

        printf("\nMas tareas realizadas? (s/n): ");
        scanf(" %c", &opcion);
    } while (opcion == 's' || opcion == 'S');
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

void ConsultarTarea(Nodo *pendientes, Nodo *realizadas, int id, const char *palabra) {
    Nodo *auxiliar;
    int encontrado = 0;

    printf("\nBuscando tarea con ID %d:\n", id);
    auxiliar = pendientes;
    while (auxiliar != NULL) {
        if (auxiliar->T.TareaID == id) {
            printf("Tarea encontrada en pendientes: %s\n", auxiliar->T.descripcion);
            encontrado = 1;
        }
        auxiliar = auxiliar->siguiente;
    }
    auxiliar = realizadas;
    while (auxiliar != NULL) {
        if (auxiliar->T.TareaID == id) {
            printf("Tarea encontrada en realizadas: %s\n", auxiliar->T.descripcion);
            encontrado = 1;
        }
        auxiliar = auxiliar->siguiente;
    }

    if (!encontrado) {
        printf("No se encontro ninguna tarea con ese ID.\n");
    }

    printf("\nBuscar por palabra clave: '%s'\n", palabra);
    auxiliar = pendientes;
    while (auxiliar != NULL) {
        if (strstr(auxiliar->T.descripcion, palabra) != NULL) {
            printf("Coincidencia en pendientes: ID %d | %s\n", auxiliar->T.TareaID, auxiliar->T.descripcion);
        }
        auxiliar = auxiliar->siguiente;
    }
    auxiliar = realizadas;
    while (auxiliar != NULL) {
        if (strstr(auxiliar->T.descripcion, palabra) != NULL) {
            printf("Coincidencia en realizadas: ID %d | %s\n", auxiliar->T.TareaID, auxiliar->T.descripcion);
        }
        auxiliar = auxiliar->siguiente;
    }
}
