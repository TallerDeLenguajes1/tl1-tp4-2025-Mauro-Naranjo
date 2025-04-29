#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct 
{
    int TareaId;
    char *Descripcion;
    int Duracion;
}Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;

Nodo * CrearListaVacia();
Nodo * CrearNodo (char *buff, int duracion, int ID);
void InsertarNodo (Nodo ** start, Nodo * Nodo);
Nodo * QuitarNodo (Nodo ** start, int ID);
void MostrarLista (Nodo ** start);

int main ()
{
    char buff[50];
    char opcion;
    int duracion, ID = 1000, idBuscado;
    Nodo * listaPendientes = CrearListaVacia();
    Nodo * listaRealizadas = CrearListaVacia();
    
    do {
        fflush(stdin);
        printf("ingrese la tarea pendiente a realizar: ");
        gets(buff);
        fflush(stdin);
        printf("ingrese la duracion de la tarea entre 10 y 100: ");
        scanf("%d", &duracion);
        Nodo * nuevoNodo = CrearNodo(buff, duracion, ID);
        ID++;
        InsertarNodo(&listaPendientes, nuevoNodo);
        
        fflush(stdin);
        printf("\nDesea agregar otra tarea? (s/n): ");
        scanf("%c", &opcion);
    } while (opcion == 's' || opcion == 'S');
    
    do {
        printf("ingrese el ID de la tarea que fue realizada: ");
        scanf("%d", &idBuscado);
        Nodo * nodoQuitado = QuitarNodo(&listaPendientes, idBuscado);
        InsertarNodo(&listaRealizadas, nodoQuitado);
        
        fflush(stdin);
        printf("\nDesea pasar otra tarea a realizada? (s/n): ");
        scanf("%c", &opcion);
    } while (opcion == 's' || opcion == 'S');
    
    puts("\nLista de tareas pendientes\n");
    MostrarLista(&listaPendientes);
    puts("\nLista de tareas realizadas\n");
    MostrarLista(&listaRealizadas);
    
    return 0;
}

Nodo * CrearListaVacia()
{
    return NULL;
}

Nodo * CrearNodo(char *buff, int duracion ,int ID)
{
    Nodo * nuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    nuevoNodo->T.TareaId = ID;
    nuevoNodo->T.Descripcion = (char *)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(nuevoNodo->T.Descripcion, buff);
    
    nuevoNodo->T.Duracion = duracion;
    nuevoNodo->Siguiente = NULL;
    
    return nuevoNodo;
}

void InsertarNodo(Nodo ** start, Nodo * Nodo)
{
    Nodo->Siguiente = *start;
    *start = Nodo;
}

Nodo * QuitarNodo (Nodo ** start, int ID)
{
    Nodo ** aux = start;
    while (aux != NULL && (*aux)->T.TareaId != ID)
    {
        aux = &(*aux)->Siguiente;
    }
    if (*aux)
    {
        Nodo * temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }
    return NULL;
}

void MostrarLista (Nodo ** start)
{
    Nodo * Aux = *start;
    while (Aux)
    {
        printf("ID de la tarea: %d\n", Aux->T.TareaId);
        printf("Descripcion de la tarea: %s\n", Aux->T.Descripcion);
        printf("Duracion de la tarea: %d\n", Aux->T.Duracion);
        Aux = Aux->Siguiente;
    }
}