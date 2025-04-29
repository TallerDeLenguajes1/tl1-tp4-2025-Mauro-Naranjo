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
Nodo * CrearNodo(char *buff, int duracion, int ID);
void InsertarNodo(Nodo ** start, Nodo * Nodo);

int main ()
{
    char buff[50];
    char opcion;
    int duracion, ID = 999;
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
        InsertarNodo(&listaPendientes, nuevoNodo);
        
        fflush(stdin);
        printf("\nDesea agregar otra tarea? (s/n): ");
        scanf("%c", &opcion);
    } while (opcion == 's' || opcion == 'S');
    
    return 0;
}

Nodo * CrearListaVacia()
{
    return NULL;
}

Nodo * CrearNodo(char *buff, int duracion ,int ID)
{
    Nodo * nuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    nuevoNodo->T.TareaId = ID++;
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